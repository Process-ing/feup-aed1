#ifndef UCCLASS_H
#define UCCLASS_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

class UcClass {
    public:
        UcClass(string dayOfTheWeek, float startTime, string classType, float classDuration);
        string get_dayOfTheWeek() const;
        string get_classType() const;
        float get_startTime() const;
        float get_classDuration() const;
        bool Overlaps(UcClass lesson) const;

    public:
        string dayOfTheWeek_;
        float startTime_;
        string classType_;
        float classDuration_;
};




#endif
