#ifndef UCCLASS_H
#define UCCLASS_H


#include <vector>
#include <string>
using namespace std;

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

    /**
     * @brief ucCode getter
     * @return ucCode
     * @author Diogo Vieira
     */
    string get_ucCode() const;

    /**
     * @brief codeOfClass getter
     * @return codeOfClass
     * @author Diogo Vieira
     */
    string get_codeOfClass() const;

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
     * @brief numberOfStudents getter
     * @return numberOfStudents
     * @author Diogo Vieira
     */
    int get_numberOfStudents() const;

    /**
     * @brief maxCapacity getter
     * @return maxCapacity
     * @author Diogo Vieira
     */
    int get_maxCapacity() const;

    /**
     * @brief Checks if two lessons overlap
     * @param lesson
     * @return true if two lessons overlap, false if they don't
     * @author Diogo Vieira
     */
    bool Overlaps(UcClass lesson) const;

    /**
     * @brief numberOfStudents establishment
     * @param newNumberOfStudents
     * @author Diogo Vieira
     */
    void set_numberOfStudents(int newNumberOfStudents);

    /**
     * @brief maxCapacity establishment
     * @param newMaxCapacity
     * @author Diogo Vieira
     */
    void set_maxCapacity(int newMaxCapacity);

private:
    string ucCode_;
    string codeOfClass_;
    string dayOfTheWeek_;
    float startTime_;
    string classType_;
    float classDuration_;
    int numberOfStudents_;
    int maxCapacity_;
};

#endif
