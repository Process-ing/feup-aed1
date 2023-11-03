/**
 * @file UcClass.h
 * Header file for class UcClass.
 */

#ifndef UCCLASS_H
#define UCCLASS_H

#include "Lesson.h"
#include <vector>
#include <string>

/**
 * @brief Represents an university class within a course unit.
 */
class UcClass {
  public:
    /**
    * @brief Constructs an UcClass instance with no lessons.
    *
    * @param uc_code Code of the UC.
    * @param class_code Code of the class.
    */
    UcClass(const std::string& uc_code, const std::string& class_code);

    /**
     * @brief Constructs an UcClass instance.
     *
     * @param uc_code Code of the UC.
     * @param class_code Code of the class.
     * @param lessons Lessons of the class.
     */
    UcClass(const std::string& uc_code, const std::string& class_code, const std::vector<Lesson>& lessons);

    /**
     * @brief Returns the UC code.
     * @return UC code.
     */
    std::string getUcCode() const;

    /**
     * @brief Returns the class code.
     * @return Class code.
     */
    std::string getClassCode() const;

    /**
     * @brief Returns the lessons of the class.
     * Complexity: O(1)
     * @return Vector of the class' lessons, sorted by start time.
     */
    std::vector<Lesson>& getLessons();

    /**
     * @brief Returns the lessons of the class.
     * Complexity: O(1)
     * @return Vector of the class' lessons, sorted by start time.
     */
    const std::vector<Lesson>& getLessons() const;

    /**
     * @brief Returns the class' academic year, based on its class code.
     * Complexity: O(1)
     * @return Academic year.
     */
    int getAcademicYear() const;

    /**
     * @brief Returns the number of students enrolled in the class.
     * Complexity: O(1)
     * @return Number of students.
     */
    int getNumberOfStudents() const;

    /**
     * @brief Increments the number of students by one.
     * Complexity: O(1)
     * @return New number of students.
     */
    int incrementNumberOfStudents();

    /**
     * @brief Decrements the number of students by one.
     * Complexity: O(1)
     * @return New number of students.
     */
    int decrementNumberOfStudents();

    /**
     * @brief Compares two UcClass objects lexicographically by UC code and class code.
     * @return True if the first is less than the second, false otherwise.
     */
    bool operator<(const UcClass& other) const;

    /**
     * @brief Checks if two UcClass objects are equal, based on their UC code and class code.
     * @return True if the two are equal, false otherwise.
     */
    bool operator==(const UcClass& other) const;

    /**
     * @brief Checks if two UcClass objects are different, based on their UC code and class code.
     * @return True if the two are distinct, false otherwise.
     */
    bool operator!=(const UcClass& other) const;

  private:
    std::string uc_code_;
    std::string class_code_;
    std::vector<Lesson> lessons_;
    int number_of_students_;
};

/**
 * @brief Reference to an UcClass instance in the dataset.
 */
typedef std::vector<UcClass>::iterator UcClassRef;

/**
 * @brief Constant reference to an UcClass instance in the dataset.
 */
typedef std::vector<UcClass>::const_iterator UcClassConstRef;

#endif
