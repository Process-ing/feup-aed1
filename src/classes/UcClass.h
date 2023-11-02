#ifndef UCCLASS_H
#define UCCLASS_H

#include "Lesson.h"
#include <vector>
#include <string>
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
     */
     UcClass();

    /**
    * Parameterized constructor for UcClass
    * @param uc_code
    * @param class_code
    * @author Diogo Vieira
    */
    UcClass(const std::string& uc_code, const std::string& class_code);

    /**
     * Parameterized constructor for UcClass
     * @param uc_code
     * @param class_codecodeOfClass
     * @param lessons
     * @author Diogo Vieira
     */
    UcClass(const std::string& uc_code, const std::string& class_code, const std::vector<Lesson>& lessons);
    std::string getUcCode() const;
    std::string getClassCode() const;
    std::vector<Lesson>& getLessons();
    const std::vector<Lesson>& getLessons() const;
    int getNumberOfStudents() const;
    void setNumberOfStudents(int new_number_of_students);
    /**
      * @brief Add a Lesson to this UcClass.
      * Adds a Lesson to the collection of lessons associated with this UcClass.
      * @param lesson The Lesson to be added to this UcClass.
      * @author Diogo Vieira
      */
    void addLesson(Lesson lesson);
    /**
    * @brief Less-than comparison operator for UcClass objects.
    * This operator overloads the '<' operator to compare two UcClass objects based on their `uc_code` and `class_code`.
    * @param other The UcClass object to compare with.
    * @return True if this UcClass's `uc_code_` is less than the `uc_code_` of the other UcClass, false otherwise.
    * @author Diogo Vieira
    */
    bool operator<(const UcClass& other) const;
    /**
     * @brief Equality operator for UcClass objects.
     * This operator overloads the '==' operator to compare two UcClass objects based on their `uc_code` and
     * `class_code`.
     * @param other The UcClass object to compare with.
     * @return True if this UcClass's `uc_code_` is equal to the `uc_code_` of the other UcClass, false otherwise.
     * @author Diogo Vieira
     */
    bool operator==(const UcClass& other) const;

    int getAcademicYear() const;
private:
    std::string uc_code_;
    std::string class_code_;
    std::vector<Lesson> lessons_;
    int number_of_students_;
};

#endif
