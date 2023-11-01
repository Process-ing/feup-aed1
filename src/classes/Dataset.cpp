#include "Student.h"
#include "UcClass.h"
#include "Dataset.h"
#include "Lesson.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <list>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;
Dataset::Dataset(){
    readUcs();
    readClasses();
    readStudents();
}
const set<Student>& Dataset::getStudents() const {
    return students_;
}
const vector<UcClass>& Dataset::getUcClasses() const {
    return uc_classes_;
}
void Dataset::readUcs() {
    static const string CLASSES_PER_UC_FILEPATH = "dataset/classes_per_uc.csv";
    ifstream classes_per_uc_file(CLASSES_PER_UC_FILEPATH);
    if (classes_per_uc_file.fail()) {
        ostringstream error_msg;
        error_msg << "Could not open file \"" << CLASSES_PER_UC_FILEPATH << '"';
        throw ios_base::failure(error_msg.str());
    }
    string line, uc_code, class_code;
    getline(classes_per_uc_file, line);
    while (getline(classes_per_uc_file, uc_code, ',')) {
        getline(classes_per_uc_file, class_code);
        uc_classes_.emplace_back(uc_code, class_code);
    }
    sort(uc_classes_.begin(), uc_classes_.end());
}
void Dataset::readClasses() {
    static const string CLASSES_FILEPATH = "dataset/classes.csv";
    static const unordered_map<string, Lesson::Type> STR_TO_TYPE = {
            { "T", Lesson::T }, { "TP", Lesson::TP }, { "PL", Lesson::PL },
    };
    static const unordered_map<string, Lesson::Weekday> STR_TO_WEEKDAY = {
            {"Monday", Lesson::MONDAY}, {"Tuesday", Lesson::TUESDAY}, {"Wednesday", Lesson::WEDNESDAY},
            {"Thursday", Lesson::THURSDAY}, {"Friday", Lesson::FRIDAY}, {"Saturday", Lesson::SATURDAY}
    };
    ifstream classes_file(CLASSES_FILEPATH);
    if (classes_file.fail()) {
        ostringstream error_msg;
        error_msg << "Could not open the file \"" << CLASSES_FILEPATH << endl;
        throw ios_base::failure(error_msg.str());
    }
    string line, class_code, uc_code, weekday_str, start, duration, type;
    getline(classes_file, line);
    while (getline(classes_file, class_code, ',')) {
        getline(classes_file, uc_code, ',');
        getline(classes_file, weekday_str, ',');
        getline(classes_file, start, ',');
        getline(classes_file, duration, ',');
        getline(classes_file, type);
        Lesson newLesson(
                stod(start),
                stod(duration) + stod(start),
                STR_TO_TYPE.at(type),
                STR_TO_WEEKDAY.at(weekday_str)
        );
        findUcClass(uc_code, class_code)->getLessons().push_back(newLesson);
    }
    for (UcClass& uc_class: uc_classes_) {
        vector<Lesson>& lessons = uc_class.getLessons();
        sort(lessons.begin(), lessons.end());
    }
}
vector<UcClass>::iterator Dataset::findUcClass(const string& uc_code, const string& class_code) {
    return equal_range(uc_classes_.begin(), uc_classes_.end(), UcClass(uc_code, class_code)).first;
}

vector<Student> Dataset::searchStudentsByAdmissionYear(int year) const {
    auto first = students_.equal_range(Student(year * 10000, "")).first,
            last = students_.equal_range(Student((year + 1) * 10000, "")).first;
    return { first, last };
}


std::set<Student>::iterator Dataset::searchStudentByCode(int student_code) const {
    return students_.find(Student(student_code, ""));
}

vector<Student> Dataset::searchStudentsByUcClass(const UcClass& uc_class) const {
    vector<Student> students_in_class;
    for (const Student& student : students_) {
        if (student.hasClass(uc_class)) {
            students_in_class.push_back(student);
        }
    }
    return students_in_class;
}

vector<Student> Dataset::searchStudentsInAtLeastNUCs(int n) const {
    vector<Student> students_in_at_least_n_ucs;
    for (const Student& student : students_) {
        if (student.getUcClasses().size() >= n) {
            students_in_at_least_n_ucs.push_back(student);
        }
    }
    return students_in_at_least_n_ucs;
}

vector<Student> Dataset::searchStudentsInUC(const string& uc_code) const {
    vector<Student> students_in_uc;
    for (const Student& student : students_) {
        for (UcClassRef ucClass : student.getUcClasses()) {
            if (ucClass->getUcCode() == uc_code) {
                students_in_uc.push_back(student);
                break;
            }
        }
    }
    return students_in_uc;
}

vector<Student> Dataset::searchStudentsInClass(const string& class_code) const {
    vector<Student> students_in_class;
    for (const Student &student: students_) {
        for (UcClassRef ucClass: student.getUcClasses()) {
            if (ucClass->getClassCode() == class_code) {
                students_in_class.push_back(student);
                break;
            }
        }
    }
    return students_in_class;
}

void Dataset::readStudents() {
    const static string STUDENT_CLASSES_PATH = "dataset/students_classes.csv";
    ifstream studentClassesFile(STUDENT_CLASSES_PATH);
    if (!studentClassesFile.is_open()) {
        cerr << "Error: Could not open the file" << endl;
        return;
    }
    string sstudent_code, student_name, uc_code, class_code, line;
    int student_code;
    getline(studentClassesFile, line);
    Student current_student(-1, "");
    list<UcClass*> classes;
    while (getline(studentClassesFile, sstudent_code, ',')) {
        student_code = stoi(sstudent_code);
        getline(studentClassesFile, student_name, ',');
        getline(studentClassesFile, uc_code, ',');
        getline(studentClassesFile, class_code);
        if (current_student.getStudentCode() != student_code) {
            if (current_student.getStudentCode() != -1)
                students_.insert(current_student);
            cout << current_student.getUcClasses().size();
            current_student = Student(student_code, student_name);
        }
        current_student.getUcClasses().emplace_back(findUcClass(uc_code,class_code));
    }
}


vector<Lesson> Dataset::getStudentLessons(const Student &student) const {
    vector<Lesson> res, temp;
    for (UcClassRef uc_class: student.getUcClasses()) {
        const vector<Lesson>& class_lessons = uc_class->getLessons();
        merge(res.begin(), res.end(), class_lessons.begin(), class_lessons.end(), temp.begin());
        res = temp;
        temp.clear();
    }
    return res;
}

vector<UcClass> Dataset::getUcClassesByClassCode(const string &class_code) const {
    vector<UcClass> res;
    for (const UcClass& uc_class: uc_classes_) {
        if (uc_class.getClassCode() == class_code)
            res.push_back(uc_class);
    }
    return res;
}

vector<Student> Dataset::searchStudentsByAcademicYear(int year) const {
    vector<Student> res;
    for (const Student& student: students_) {
        if (student.getAcademicYear() == year)
            res.push_back(student);
    }
    return res;
}