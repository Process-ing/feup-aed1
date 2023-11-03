#include <algorithm>
#include "Student.h"

using namespace std;

Student::Student(int student_code, const std::string &student_name) {
    student_code_ = student_code;
    student_name_ = student_name;
}

int Student::getStudentCode() const { return student_code_; }

std::string Student::getStudentName() const { return student_name_; }

std::list<UcClassConstRef> &Student::getUcClasses() { return uc_classes_; }

const std::list<UcClassConstRef> &Student::getUcClasses() const { return uc_classes_; }

bool Student::isInClass(const UcClass &uc_class) const {
    for (UcClassConstRef student_class: uc_classes_) {
        if (*student_class == uc_class)
            return true;
    }
    return false;
}

bool Student::operator<(const Student &student) const{
    return this->student_code_ < student.student_code_;
}

int Student::getAdmissionYear() const {
    return student_code_ / 100000;
}

int Student::getAcademicYear() const {
    int res = -1;
    for (UcClassConstRef uc_class: uc_classes_)
        res = max(res, uc_class->getAcademicYear());
    return res;
}

bool Student::isInUc(const std::string &uc_code) const {
    for (UcClassConstRef student_class: uc_classes_) {
        if (student_class->getUcCode() == uc_code)
            return true;
    }
    return false;
}

std::vector<Lesson> Student::getLessons() const {
    vector<Lesson> res;
    for (UcClassConstRef uc_class: uc_classes_)
        res.insert(res.end(), uc_class->getLessons().begin(), uc_class->getLessons().end());
    sort(res.begin(), res.end());
    return res;
}

vector<Lesson> Student::getLessonsIgnoring(const UcClass &class_to_ignore) const {
    vector<Lesson> res;
    for (UcClassConstRef uc_class: uc_classes_) {
        if (*uc_class == class_to_ignore)
            continue;
        res.insert(res.end(), uc_class->getLessons().begin(), uc_class->getLessons().end());
    }
    sort(res.begin(), res.end());
    return res;
}

bool Student::lessonsIncompatibleWith(const Lesson &lesson) const {
    vector<Lesson> student_lessons = getLessons();

    for (const Lesson& student_lesson: student_lessons) {
        if (student_lesson.overlaps(lesson) && !student_lesson.isCompatibleWith(lesson))
            return true;
    }
    return false;
}

bool Student::lessonsIncompatibleWith(const Lesson &lesson, const UcClass& class_to_ignore) const {
    vector<Lesson> student_lessons = getLessonsIgnoring(class_to_ignore);

    for (const Lesson& student_lesson: student_lessons) {
        if (student_lesson.overlaps(lesson) && !student_lesson.isCompatibleWith(lesson))
            return true;
    }
    return false;
}
