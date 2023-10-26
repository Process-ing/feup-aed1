#include "UcClass.h"

UcClass::UcClass(string ucCode, string codeOfClass, vector<Lesson> lessons) {
    this->ucCode_ = ucCode;
    this->codeOfClass_ = codeOfClass;
    this->lessons_ = lessons;
    this->numberOfStudents_ = 0;
    this->maxCapacity_ = 0;
}

string UcClass::getUcCode() {
    return ucCode_;
}

string UcClass::getCodeOfClass(){
    return codeOfClass_;
}

int UcClass::getNumberOfStudents() {
    return numberOfStudents_;
}

int UcClass::getMaxCapacity() {
    return maxCapacity_;
}

void UcClass::setMaxCapacity(int newMaxCapacity) {
    maxCapacity_ = newMaxCapacity;
}

void UcClass::setNumberOfStudents(int newNumberOfStudents) {
    numberOfStudents_ = newNumberOfStudents;
}

vector<Lesson> UcClass::getLessons(){
    return lessons_;
}


