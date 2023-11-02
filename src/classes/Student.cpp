#include <algorithm>
#include "Student.h"

using namespace std;

Student::Student(int student_code, const std::string &student_name) {
    student_code_ = student_code;
    student_name_ = student_name;
}

int Student::getStudentCode() const { return student_code_; }

std::string Student::getStudentName() const { return student_name_; }

std::list<UcClassRef> &Student::getUcClasses() { return uc_classes_; }

const std::list<UcClassRef> &Student::getUcClasses() const { return uc_classes_; }

bool Student::isInClass(const UcClass &uc_class) const {
    for (UcClassRef student_class: uc_classes_) {
        if (*student_class == uc_class)
            return true;
    }
    return false;
}

bool Student::isInUc(const std::string &uc_code) const {
    for (UcClassRef student_class: uc_classes_) {
        if (student_class->getUcCode() == uc_code)
            return true;
    }
    return false;
}

std::vector<Lesson> Student::getLessons() const {
    vector<Lesson> res, temp;
    for (UcClassRef uc_class: uc_classes_) {
        const vector<Lesson>& class_lessons = uc_class->getLessons();
        merge(res.begin(), res.end(), class_lessons.begin(), class_lessons.end(), back_inserter(temp));
        res = temp;
        temp.clear();
    }
    return res;
}

vector<Lesson> Student::getLessonsIgnoring(const UcClass &class_to_ignore) const {
    vector<Lesson> res, temp;
    for (UcClassRef uc_class: uc_classes_) {
        if (*uc_class == class_to_ignore)
            continue;
        const vector<Lesson>& class_lessons = uc_class->getLessons();
        merge(res.begin(), res.end(), class_lessons.begin(), class_lessons.end(), back_inserter(temp));
        res = temp;
        temp.clear();
    }
    return res;
}

bool Student::lessonsOverlapsWith(const Lesson &lesson) const {
    vector<Lesson> student_lessons = getLessons();
    auto it = lower_bound(
            student_lessons.begin(),
            student_lessons.end(),
            Lesson(0.0, 0.0, Lesson::T, lesson.getWeekday())
    );

    while (it != student_lessons.end() && it->getStart() < lesson.getEnd()) {
        if (it->overlaps(lesson) && !it->isCompatibleWith(lesson))
            return true;
        it++;
    }
    return false;
}

bool Student::lessonsOverlapsWith(const Lesson &lesson, const UcClass& class_to_ignore) const {
    vector<Lesson> student_lessons = getLessonsIgnoring(class_to_ignore);
    auto it = lower_bound(
            student_lessons.begin(),
            student_lessons.end(),
            Lesson(0.0, 0.0, Lesson::T, lesson.getWeekday())
    );

    while (it != student_lessons.end() && it->getStart() < lesson.getEnd()) {
        if (it->overlaps(lesson) && !it->isCompatibleWith(lesson))
            return true;
        it++;
    }
    return false;
}

bool Student::operator<(const Student &student) const {
    return this->student_code_ < student.student_code_;
}