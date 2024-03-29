#include "UcClass.h"

using namespace std;

UcClass::UcClass(const string& uc_code, const string& class_code) {
    this->uc_code_ = uc_code;
    this->class_code_ = class_code;
    this->number_of_students_ = 0;
}

UcClass::UcClass(const string& uc_code, const string& class_code, const vector<Lesson>& lessons) {
    this->uc_code_ = uc_code;
    this->class_code_ = class_code;
    this->lessons_ = lessons;
    this->number_of_students_ = 0;
}

string UcClass::getUcCode() const {
    return uc_code_;
}

string UcClass::getClassCode() const{
    return class_code_;
}

int UcClass::getNumberOfStudents() const {
    return number_of_students_;
}

int UcClass::incrementNumberOfStudents() {
    return ++number_of_students_;
}

int UcClass::decrementNumberOfStudents() {
    return --number_of_students_;
}

vector<Lesson>& UcClass::getLessons() {
    return lessons_;
}

const vector<Lesson>& UcClass::getLessons() const {
    return lessons_;
}

bool UcClass::operator<(const UcClass& other) const {
    return uc_code_ < other.uc_code_ || (uc_code_ == other.uc_code_ && class_code_ < other.class_code_);
}

bool UcClass::operator==(const UcClass &other) const {
    return uc_code_ == other.uc_code_ && class_code_ == other.class_code_;
}

bool UcClass::operator!=(const UcClass &other) const {
    return uc_code_ != other.uc_code_ || class_code_ != other.class_code_;
}

int UcClass::getAcademicYear() const {
    return class_code_[0] - '0';
}
