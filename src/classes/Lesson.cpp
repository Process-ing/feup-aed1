#include "Lesson.h"

Lesson::Lesson(std::pair<int, int> start, std::pair<int, int> end, Type type, Weekday weekday) {
    start_ = start;
    end_ = end;
    type_ = type;
    weekday_ = weekday;
}

std::pair<int, int> Lesson::getStart() const { return start_; }

std::pair<int, int> Lesson::getEnd() const { return end_; }

Lesson::Type Lesson::getType() const { return type_; }

Lesson::Weekday Lesson::getWeekday() const { return weekday_; }

bool Lesson::operator<(const Lesson &lesson) {
    std::pair<int,int> start1 = this->start_, start2 = lesson.start_;
    return start1.first < start2.first || (start1.first == start2.first && start1.second < start2.second);
}

bool Lesson::overlaps(const Lesson &lesson) {
    std::pair<int,int> start1 = this->start_, start2 = lesson.start_, end1 = this->end_, end2 = lesson.end_;
    return start1 < end2 && start2 < end1;
}