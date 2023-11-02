#include "Lesson.h"

Lesson::Lesson(double start, double end, Type type, Weekday weekday) {
    start_ = start;
    end_ = end;
    type_ = type;
    weekday_ = weekday;
}

double Lesson::getStart() const { return start_; }

double Lesson::getEnd() const { return end_; }

Lesson::Type Lesson::getType() const { return type_; }

Lesson::Weekday Lesson::getWeekday() const { return weekday_; }

bool Lesson::operator<(const Lesson &lesson) const {
    return weekday_ < lesson.weekday_ || (weekday_ == lesson.weekday_ && start_ < lesson.start_);
}

bool Lesson::overlaps(const Lesson &lesson) const {
    return weekday_ == lesson.weekday_ && start_ < lesson.end_ && lesson.start_ < this->end_;
}

bool Lesson::isCompatibleWith(const Lesson &lesson) const {
    return type_ == T || lesson.type_ == T;
}
