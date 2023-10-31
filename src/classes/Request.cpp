#include "Request.h"
#include <iostream>

Request::Request(Request::Type type, Student& student, UcClass& target_class) {
    type_ = type;
    student_ = &student;
    target_class_ = &target_class;
}

void Request::perform(Dataset &dataset) {
    switch (type_) {
        case ADD:
            for (UcClass* const& c : student_->getUcClasses()) {
                if (c->getUcCode() == target_class_->getUcCode()) {
                    std::cout << "Request failed: already in this UC" << std::endl;
                    break;
                }
            }
            //if (target_class_->getNumberOfStudents() == max) {
            //    std::cout << "Request failed: class full" << std::endl;
            //    break;
            //}
            for (UcClass* const& c : student_->getUcClasses()) {
                if (c->getNumberOfStudents() - target_class_->getNumberOfStudents() == 4
                 || c->getNumberOfStudents() - target_class_->getNumberOfStudents() == -4) {
                    std::cout << "Request failed: entering this class would disturb class occupation balance" << std::endl;
                    break;
                }
            }
            for (UcClass* const& c : student_->getUcClasses()) {
                for (Lesson const& l : c->getLessons()) {
                    if (l.getType() == Lesson::TP || l.getType() == Lesson::PL) {
                        for (Lesson const &tl: target_class_->getLessons()) {
                            if (tl.getType() == Lesson::TP || tl.getType() == Lesson::PL) {
                                if (l.overlaps(tl)) {
                                    std::cout << "Request failed: target class's lessons overlap with your schedule" << std::endl;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            student_->getUcClasses().insert(student_->getUcClasses().end(), target_class_);
            break;
        case REMOVE:
            //TODO
            break;
        case SWITCH:
            //TODO
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
