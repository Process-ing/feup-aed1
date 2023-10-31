#include "Request.h"
#include <iostream>

Request::Request(Request::Type type, Student& student, UcClass& current_class, UcClass& target_class) {
    type_ = type;
    student_ = &student;
    current_class_ = &current_class;
    target_class_ = &target_class;
}

void Request::perform(Dataset &dataset) {
    switch (type_) {
        case ADD:
            if (!(alreadyInUc(target_class_) || addBalanceDisturbance(dataset) || overlaping()))
                student_->getUcClasses().insert(student_->getUcClasses().end(), dataset.getUcClasses().find(*target_class_));
            break;
        case REMOVE:
            if (alreadyInUc(current_class_) && !removeBalanceDisturbance(dataset))
                student_->getUcClasses().remove(dataset.getUcClasses().find(*current_class_));
            break;
        case SWITCH:
            if (alreadyInUc(current_class_) && !removeBalanceDisturbance(dataset) &&
                !(alreadyInUc(target_class_) || addBalanceDisturbance(dataset) || overlaping())) {
                student_->getUcClasses().remove(dataset.getUcClasses().find(*current_class_));
                student_->getUcClasses().insert(student_->getUcClasses().end(), dataset.getUcClasses().find(*target_class_));
            }
            break;
    }
}

Request::Type Request::getType() const {
    return type_;
}

const Student& Request::getStudent() const {
    return *student_;
}

const UcClass& Request::getTargetClass() const {
    return *target_class_;
}

bool Request::alreadyInUc(UcClass* what_class) {
    for (auto const& c : student_->getUcClasses()) {
        if (c->getUcCode() == target_class_->getUcCode()) {
            return true;
        }
    }
    return false;
}
// bool Request::classFull() {
//  if (target_class_->getNumberOfStudents() == max) {
//      return true;
//  }
//  return false;
//}
bool Request::addBalanceDisturbance(Dataset &dataset) {
    for (auto const& c : dataset.getUcClasses()) {
        if (c.getUcCode() == target_class_->getUcCode() && c.getNumberOfStudents() - target_class_->getNumberOfStudents() == -4) {
            return true;
        }
    }
    return false;
}

bool Request::removeBalanceDisturbance(Dataset &dataset) {
    for (auto const& c : dataset.getUcClasses()) {
        if (c.getUcCode() == current_class_->getUcCode() && c.getNumberOfStudents() - current_class_->getNumberOfStudents() == 4) {
            return true;
        }
    }
    return false;
}
bool Request::overlaping() {
    for (auto const& c : student_->getUcClasses()) {
        for (Lesson const& l : c->getLessons()) {
            if (l.getType() == Lesson::TP || l.getType() == Lesson::PL) {
                for (Lesson const &tl: target_class_->getLessons()) {
                    if (tl.getType() == Lesson::TP || tl.getType() == Lesson::PL) {
                        if (l.overlaps(tl)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}
