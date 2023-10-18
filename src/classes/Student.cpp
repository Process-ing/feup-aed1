//
// Created by memechanic on 18-10-2023.
//

#include "Student.h"

Student::Student(int StudentCode, std::string StudentName, std::string UcCode, std::string ClassCode) {
    StudentCode_ = StudentCode;
    StudentName_ = StudentName;
    UcCode_ = UcCode;
    ClassCode_ = ClassCode;
}

int Student::getStudentCode() const {return StudentCode_;}

std::string Student::getStudentName() const {return StudentName_;}

std::string Student::getUcCode() const {return UcCode_;}

std::string Student::getClassCode() const {return ClassCode_;}

void Student::setStudentCode(int StudentCode) {StudentCode_ = StudentCode;}

void Student::setStudentName(std::string StudentName) {StudentName_ = StudentName;}

void Student::setUcCode(std::string UcCode) {UcCode_ = UcCode;}

void Student::setClassCode(std::string ClassCode) {ClassCode_ = ClassCode;}