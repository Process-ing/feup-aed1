#include "UcClass.h"
#include <string>
using namespace std;

UcClass::UcClass(string dayOfTheWeek, float startTime, string classType, float classDuration) {
    this->dayOfTheWeek_ = dayOfTheWeek;
    this->startTime_ = startTime;
    this->classType_ = classType;
    this->classDuration_ = classDuration;
}

string UcClass::get_dayOfTheWeek() const {
    return this->dayOfTheWeek_;
}

float UcClass::get_startTime() const {
    return this->startTime_;
}

string UcClass::get_classType() const{
    return this->classType_;
}

float UcClass::get_classDuration() const {
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


