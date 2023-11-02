#include "Request.h"
#include <utility>

using namespace std;

Request::Request(Request::Type type, int student_code, UcClassRef current_class, UcClassRef target_class) {
    student_code_ = student_code;
    type_ = type;
    current_class_ = current_class;
    target_class_ = target_class;
}

Request::Type Request::getType() const {
    return type_;
}

int Request::getStudentCode() const {
    return student_code_;
}

UcClassRef Request::getCurrentClass() const {
    return current_class_;
}

UcClassRef Request::getTargetClass() const {
    return target_class_;
}

