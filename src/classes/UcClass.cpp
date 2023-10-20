#include "UcClass.h"

UcClass::UcClass(string ucCode, string codeOfClass, string dayOfTheWeek, float startTime, string classType, float classDuration) {
    this->ucCode_ = ucCode;
    this->codeOfClass_ = codeOfClass;
    this->dayOfTheWeek_ = dayOfTheWeek;
    this->startTime_ = startTime;
    this->classType_ = classType;
    this->classDuration_ = classDuration;
    this->numberOfStudents_ = 0;
    this->maxCapacity_ = 0;
}

string UcClass::get_ucCode() const {
    return ucCode_;
}

string UcClass::get_codeOfClass() const {
    return codeOfClass_;
}

int UcClass::get_numberOfStudents() const {
    return numberOfStudents_;
}

int UcClass::get_maxCapacity() const {
    return maxCapacity_;
}

void UcClass::set_maxCapacity(int newMaxCapacity) {
    maxCapacity_ = newMaxCapacity;
}

void UcClass::set_numberOfStudents(int newNumberOfStudents) {
    numberOfStudents_ = newNumberOfStudents;
}

string UcClass::get_dayOfTheWeek() const {
    return this->dayOfTheWeek_;
}

float UcClass::get_startTime() const {
    return this->startTime_;
}

string UcClass::get_classType() const {
    return this->classType_;
}

float UcClass::get_classDuration() const {
    return this->classDuration_;
}

bool UcClass::Overlaps(UcClass lesson) const {
    if (this->dayOfTheWeek_ == lesson.dayOfTheWeek_) {
        float thisEnd = this->startTime_ + this->classDuration_;
        float lessonEnd = lesson.startTime_ + lesson.classDuration_;
        if (this->startTisme_ <= lessonEnd && thisEnd >= lesson.startTime_) {
            return true;
        }
    }
    return false;
}

