#include "Student.h"
#include "UcClass.h"
#include "Dataset.h"
#include "Lesson.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <map>
#include <set>
using namespace std;

Dataset::Dataset(){
    UcReader();
    UcClassReader();
}

const set<Student>& Dataset::getStudents() const {
    return students_;
}

const set<UcClass>& Dataset::getUcClasses() const {
    return uc_classes_;
}

void Dataset::UcReader() {
    static const string CLASSES_FILEPATH = "files/classes.csv";
    ifstream classes_file(CLASSES_FILEPATH);
    if (!classes_file.is_open()) {
        ostringstream error_msg;
        error_msg << "Could not open file \"" << CLASSES_FILEPATH << '"';
        throw ios_base::failure(error_msg.str());
    }
    string line, uc_code, code_of_class;
    getline(classes_file, line);
    while (getline(classes_file, code_of_class, ',')) {
        getline(classes_file, uc_code, ',');
        uc_classes_.insert(UcClass(uc_code, code_of_class));
    }
}

void Dataset::UcClassReader() {
    static const string CLASSES_FILEPATH = "files/classes.csv";
    ifstream classes_file("../files/classes.csv");
    if (!classes_file.is_open()) {
        ostringstream error_msg;
        error_msg << "Could not open the file \"" << CLASSES_FILEPATH << endl;
        throw ios_base::failure(error_msg.str());
    }
    string line, code_of_class, uc_code, weekday_str, start, duration, type;
    vector<Lesson> lessons;

    getline(classes_file, line);
    while (getline(classes_file, line)) {
        stringstream ss(line);
        getline(ss, code_of_class, ',');
        getline(ss, uc_code, ',');
        getline(ss, weekday_str, ',');
        getline(ss, start, ',');
        getline(ss, duration, ',');
        getline(ss, type);
        Lesson::Type lesson_type;
        if (type == "T") {
            lesson_type = Lesson::T;
        } else if (type == "TP")
            lesson_type = Lesson::TP;
        else if (type == "PL") {
            lesson_type = Lesson::PL;
        }
        Lesson::Weekday weekday;
        if (weekday_str == "Monday") {
            weekday = Lesson::Monday;
        } else if (weekday_str == "Tuesday") {
            weekday = Lesson::Tuesday;
        } else if (weekday_str == "Wednesday") {
            weekday = Lesson::Wednesday;
        } else if (weekday_str == "Thursday") {
            weekday = Lesson::Thursday;
        } else if (weekday_str == "Friday") {
            weekday = Lesson::Friday;
        } else if (weekday_str == "Saturday") {
            weekday = Lesson::Saturday;
        }
        Lesson newLesson(stod(start), stod(duration) + stod(start), lesson_type, weekday);
        UcClass temporaryUcClass = findUcClass(uc_code, code_of_class);
        temporaryUcClass.addLesson(newLesson);
    }
}

UcClass Dataset::findUcClass(const string& uc_code, const string& code_of_class) {
    UcClass tempUcClass(uc_code, code_of_class, vector<Lesson>());
    for (const UcClass& ucClass : uc_classes_) {
        if (ucClass.getUcCode() == uc_code && ucClass.getClassCode() == code_of_class) {
            return ucClass;
        }
    }

    cout << "This UcClass could not be found." << endl;
    return UcClass();
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
        for (UcClass* ucClass : student.getUcClasses()) {
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
        for (const UcClass *ucClass: student.getUcClasses()) {
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