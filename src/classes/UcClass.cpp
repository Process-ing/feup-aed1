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

string UcClass::getUcCode() const {
    return ucCode_;
}

string UcClass::getCodeOfClass() const {
    return codeOfClass_;
}

int UcClass::getNumberOfStudents() const {
    return numberOfStudents_;
}

int UcClass::getMaxCapacity() const {
    return maxCapacity_;
}

void UcClass::setMaxCapacity(int newMaxCapacity) {
    maxCapacity_ = newMaxCapacity;
}

void UcClass::setNumberOfStudents(int newNumberOfStudents) {
    numberOfStudents_ = newNumberOfStudents;
}

string UcClass::getDayOfTheWeek() const {
    return this->dayOfTheWeek_;
}

float UcClass::getStartTime() const {
    return this->startTime_;
}

string UcClass::getClassType() const {
    return this->classType_;
}

float UcClass::getClassDuration() const {
    return this->classDuration_;
}

bool UcClass::Overlaps(UcClass lesson) const {
    if (this->dayOfTheWeek_ == lesson.dayOfTheWeek_) {
        float thisEnd = this->startTime_ + this->classDuration_;
        float lessonEnd = lesson.startTime_ + lesson.classDuration_;
        if (this->startTime_ <= lessonEnd && thisEnd >= lesson.startTime_) {
            return true;
        }
    }
    return false;
}

