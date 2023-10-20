#ifndef UCCLASS_H
#define UCCLASS_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

class UcClass {
    public:
        /**
         * @brief UcClass parameterized constructor
         * @param dayOfTheWeek
         * @param startTime
         * @param classType
         * @param classDuration
         * @author Diogo Vieira
         */
        UcClass(string dayOfTheWeek, float startTime, string classType, float classDuration);

        /**
         * @brief dayOfTheWeek getter
         * @return dayOfTheWeek
         * @author Diogo Vieira
         */
        string get_dayOfTheWeek() const;

        /**
         * @brief classType getter
         * @return classType
         * @author Diogo Vieira
         */
        string get_classType() const;

        /**
         * @brief startTime getter
         * @return startTime
         * @author Diogo Vieira
         */
        float get_startTime() const;

        /**
         * @brief classDuration getter
         * @return classDuration
         * @author Diogo Vieira
         */
        float get_classDuration() const;

        /**
         * @brief Checks if two lessons overlap
         * @param lesson
         * @return true if two lessons overlaps, false if they don´t
         * @author Diogo Vieira
         */
        bool Overlaps(UcClass lesson) const;

    public:
        string dayOfTheWeek_;
        float startTime_;
        string classType_;
        float classDuration_;
};




#endif
