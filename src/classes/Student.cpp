#include "Student.h"

Student::Student(int StudentCode, std::string StudentName) {
    StudentCode_ = StudentCode;
    StudentName_ = StudentName;
}

int Student::getStudentCode() const { return StudentCode_; }

std::string Student::getStudentName() const { return StudentName_; }

std::list<std::string> &Student::getUcClasses() { return UcClasses_; }

const std::list<std::string> &Student::getUcClasses() const { return UcClasses_; }