#include <sstream>
#include <iomanip>
#include "Lesson.h"

using namespace std;

Lesson::Lesson(double start, double end, Type type, Weekday weekday) {
    start_ = start;
    end_ = end;
    type_ = type;
    weekday_ = weekday;
}

double Lesson::getStart() const { return start_; }

double Lesson::getEnd() const { return end_; }

string Lesson::getFormattedStart() const {
    ostringstream res;
    res << setfill('0') << setw(2) << (int)start_ << ':' << setw(2) << (int)((start_ - (int)start_) * 60);
    return res.str();
}

string Lesson::getFormattedEnd() const {
    ostringstream res;
    res << setfill('0') << setw(2) << (int)end_ << ':' << setw(2) << (int)((end_ - (int)end_) * 60);
    return res.str();
}

Lesson::Type Lesson::getType() const { return type_; }

Lesson::Weekday Lesson::getWeekday() const { return weekday_; }

bool Lesson::operator<(const Lesson &lesson) const {
    return weekday_ < lesson.weekday_ || (weekday_ == lesson.weekday_ && start_ < lesson.start_);
}

bool Lesson::overlaps(const Lesson &lesson) const {
    return weekday_ == lesson.weekday_ && start_ < lesson.end_ && lesson.start_ < this->end_;
}