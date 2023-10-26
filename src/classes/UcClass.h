#ifndef UCCLASS_H
#define UCCLASS_H

#include "Lesson.h"
#include <vector>
#include <string>
using namespace std;
/**
 * @class UcClass
 * This class represents a university class within a course.
 * It provides information about the class, such as its code, day of the week, start time,
 * class type, class duration, and related student capacity.
 * The class allows for checking whether two classes overlap in terms of their schedules.
 * It also provides static methods for accessing and modifying class attributes at a class-wide level.
 *
 * @author Diogo Vieira
 */
class UcClass {
public:
    /**
     * Parameterized constructor for UcClass
     * @param ucCode
     * @param codeOfClass
     * @param dayOfTheWeek
     * @param startTime
     * @param classType
     * @param classDuration
     * @author Diogo Vieira
     */
    UcClass(string ucCode, string codeOfClass, string dayOfTheWeek, float startTime, string classType, float classDuration);
    static string getUcCode();
    static string getCodeOfClass();
    static string getDayOfTheWeek();
    static string getClassType();
    static float getStartTime();
    static float getClassDuration();
    static int getNumberOfStudents();
    static int getMaxCapacity();

    /**
     * @brief Checks if two lessons overlap
     * @param lesson
     * @return true if two lessons overlap, false if they don't
     * @author Diogo Vieira
     */
    bool Overlaps(UcClass lesson) const;
    static void setnumberOfStudents(int newNumberOfStudents);
    static void setmaxCapacity(int newMaxCapacity);

private:
    string ucCode_;
    string codeOfClass_;
    string dayOfTheWeek_;
    float startTime_;
    string classType_;
    vector<Lesson> lessons_;
    float classDuration_;
    int numberOfStudents_;
    static int maxCapacity_;
};

#endif
