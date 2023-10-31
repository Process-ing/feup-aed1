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
    vector<Student> students_by_year;
    for (const Student& student : students_) {
        int student_code = student.getStudentCode();
        int student_year = student_code / 10000;

        if (student_year == year) {
            students_by_year.push_back(student);
        }
    }
    if (students_by_year.empty()) {
        cout << "No students admitted in the year " << year << endl;
    }
    return students_by_year;
}

vector<Student> Dataset::searchStudentsByCode(int student_code) const {
    vector<Student> the_student;
    for (const Student& student : students_) {
        if (student.getStudentCode() == student_code) {
            the_student.push_back(student);
        }
    }
    if (the_student.empty()) {
        cout << "No student with code " << student_code << " was found." << endl;
    }
    return the_student;
}

vector<Student> Dataset::searchStudentsByUcClass(const UcClass& uc_class) const {
    vector<Student> students_in_class;
    for (const Student& student : students_) {
        if (student.hasClass(uc_class)) {
            students_in_class.push_back(student);
        }
    }
    if (students_in_class.empty()) {
        cout << "No students enrolled in the UC class: " << uc_class.getClassCode() << endl;
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
    if (students_in_at_least_n_ucs.empty()) {
        cout << "No students enrolled in at least " << n << " UCs." << endl;
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
    if (students_in_uc.empty()) {
        cout << "No students enrolled in the UC: " << uc_code << endl;
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
    if (students_in_class.empty()) {
        cout << "No students enrolled in class: " << class_code << endl;
    }
    return students_in_class;
}

void Dataset::readStudents() {
    const static string STUDENT_CLASSES_PATH = "../dataset/students_classes.csv";
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
            students_.insert(current_student);
            current_student = Student(student_code, student_name);
        }
        current_student.getUcClasses().emplace_back(findUcClass(uc_code,class_code));
    }
}
