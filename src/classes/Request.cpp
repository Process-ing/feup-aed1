#include "Request.h"

Request::Request(Request::Type type, Student& student, UcClass& target_class) {
    type_ = type;
    student_ = &student;
    target_class_ = &target_class;
}

void Request::perform(Dataset &dataset) {
    switch (type_) {
        case ADD:
            //TODO
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