#include "Student.h"

Student::Student(int student_code, const std::string &student_name) {
    student_code_ = student_code;
    student_name_ = student_name;
}

int Student::getStudentCode() const { return student_code_; }

std::string Student::getStudentName() const { return student_name_; }

std::list<UcClass*> &Student::getUcClasses() { return uc_classes_; }

const std::list<UcClass*> &Student::getUcClasses() const { return uc_classes_; }

bool Student::hasClass(const UcClass &uc_class) const {
    for (UcClass *student_class: uc_classes_) {
        if (*student_class == uc_class)
            return true;
    }
    return false;
}

bool Student::operator<(const Student &student) const{
    return this->student_code_ < student.student_code_;
}