#include "UcClass.h"

UcClass::UcClass(string uc_code, string code_of_class, vector<Lesson> lessons) {
    this->uc_code_ = uc_code;
    this->class_code_ = code_of_class;
    this->lessons_ = lessons;
    this->number_of_students_ = 0;
    this->max_capacity_ = 0;
}

string UcClass::getUcCode() {
    return uc_code_;
}

string UcClass::getCodeOfClass(){
    return class_code_;
}

int UcClass::getNumberOfStudents() {
    return number_of_students_;
}

int UcClass::getMaxCapacity() {
    return max_capacity_;
}

void UcClass::setMaxCapacity(int new_max_capacity) {
    max_capacity_ = new_max_capacity;
}

void UcClass::setNumberOfStudents(int new_number_of_students) {
    number_of_students_ = new_number_of_students;
}

vector<Lesson> UcClass::getLessons(){
    return lessons_;
}

void UcClass::addLesson(Lesson lesson) {
    lessons_.push_back(lesson);
}

bool UcClass::operator<(const UcClass& other) const {
    return uc_code_ < other.uc_code_ || (uc_code_ == other.uc_code_ && class_code_ < other.class_code_);
}

bool UcClass::operator==(const UcClass &other) const {
    return uc_code_ == other.uc_code_ && class_code_ == other.class_code_;
}
