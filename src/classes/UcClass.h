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
     * Default constructor for UcClass
     * @author Diogo Vieira
     * /
    UcClass();
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
    UcClass(string uc_code, string code_of_class, vector<Lesson> lessons);
    static string getUcCode();
    static string getCodeOfClass();
    static vector<Lesson> getLessons();
    static int getNumberOfStudents();
    static int getMaxCapacity();
    static void setNumberOfStudents(int new_number_of_students);
    static void setMaxCapacity(int new_max_capacity);

private:
    static string uc_code_;
    static string code_of_class_;
    static vector<Lesson> lessons_;
    static int number_of_students_;
    static int max_capacity_;
};

#endif
