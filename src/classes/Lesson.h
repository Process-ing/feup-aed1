//
// Created by memechanic on 18-10-2023.
//

#ifndef FEUP_AED1_LESSON_H
#define FEUP_AED1_LESSON_H
#include <utility>


class Lesson {
private:
    std::pair<int, int> start_;
    std::pair<int, int> end_;
public:
    enum ClassType_ {T,TP,PL};
};

#endif //FEUP_AED1_LESSON_H
