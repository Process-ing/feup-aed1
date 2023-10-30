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
#include <d2d1helper.h>

using namespace std;

Dataset::Dataset() = default;

const set<Student>& Dataset::getStudents() const {
    return students;
}

const set<UcClass>& Dataset::getUcClasses() const {
    return ucClasses;
}

const vector<UcClass>& Dataset::getAllClasses() const {
    return all_classes;
}
void Dataset::UcReader() {
    vector<UcClass> ucClasses;
    set<UcClass> temporary;
    ifstream ucClassFile("../files/classes.csv");
    if (!ucClassFile.is_open()) {
        cout << "Error: Could not open the file " << endl;
        return;
    }
    string line, uc_code, code_of_class;
    getline(ucClassFile, line);
    while (getline(ucClassFile, line)) {
        vector<Lesson> empty;
        istringstream ss(line);
        getline(ss, code_of_class, ',');
        getline(ss, uc_code, ',');
        temporary.insert(UcClass(uc_code, code_of_class, empty));
    }
    for (const UcClass& ucClass : temporary) {
        all_classes.push_back(ucClass);
    }
}

void Dataset::UcClassReader() {
    ifstream ucClassFile("../files/classes.csv");
    if (!ucClassFile.is_open()) {
        cout << "Error: Could not open the file " <<  endl;
        return;
    }
    string line, code_of_class, uc_code, weekday_str, start, duration, type;
    vector<Lesson> lessons;

    getline(ucClassFile, line);
    while (getline(ucClassFile, line)) {
        stringstream ss(line);
        getline(ss, code_of_class, ',');
        getline(ss, uc_code, ',');
        getline(ss, weekday_str, ',');
        getline(ss, start, ',');
        getline(ss, duration, ',');
        getline(ss, type, '\r');
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
        Lesson newLesson(stod(start), stod(duration)+stod(start), lesson_type, weekday);
        UcClass temporaryUcClass = findUcClass(uc_code, code_of_class);
        temporaryUcClass.addLesson(newLesson);
    }
}

UcClass Dataset::findUcClass(string uc_code, string code_of_class) {
    UcClass tempUcClass(uc_code, code_of_class, vector<Lesson>());
    for (const UcClass &ucClass: all_classes)
        if (ucClass.getUcCode() == uc_code && ucClass.getCodeOfClass() == code_of_class) {
            return ucClass;
        }

    cout << "This UcClass could not be found." << endl;
    return UcClass();
}

vector<Student> Dataset::searchStudentsByYear(int year) const {
    vector<Student> students_by_year;
    for (const Student &student: students) {
        int student_code = student.getStudentCode();
        int student_year = student_code / 10000;

        if (student_year == year) {
            students_by_year.push_back(student);
        }
    }
    return students_by_year;
}

vector<Student> Dataset::searchStudentsByClass(string ucclass_code) const {
    vector<Student> students_in_class;
    for (const Student& student : students) {
        if (student.studentClass(ucclass_code)) {
            students_in_class.push_back(student);
        }
    }
    return students_in_class;
}