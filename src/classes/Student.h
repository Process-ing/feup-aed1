/**
 * @file Student.h
 * Header file for class Student.
 */

#ifndef FEUP_AED1_STUDENT_H
#define FEUP_AED1_STUDENT_H
#include "UcClass.h"
#include <list>
#include <set>
#include <string>
#include <set>


/**
 * Represents a student and its information.
 */
class Student {
  private:
    int student_code_;
    std::string student_name_;
    std::list<UcClassConstRef> uc_classes_;

  public:
    /**
     * @brief Constructs a Student instance.
     *
     * @param student_code Code of the student.
     * @param student_name Name of the student.
     */
    Student(int student_code, const std::string &student_name);

    /**
     * @brief Returns the student's code.
     * @return Student code.
     */
    int getStudentCode() const;

    /**
     * @brief Returns the student's name.
     * @return Student name.
     */
    std::string getStudentName() const;

    /**
     * @brief Returns the classes the student is enrolled in.
     * Complexity: O(1)
     *
     * @return List of constant references to the UcClasses.
     */
    std::list<UcClassConstRef> &getUcClasses();

    /**
     * @brief Returns the classes the student is enrolled in.
     * Complexity: O(1)
     *
     * @return List of constant references to the UcClasses.
     */
    const std::list<UcClassConstRef> &getUcClasses() const;

    /**
     * @brief Checks if the user is enrolled in the class.
     * Complexity: O(n), where n is the number of the student's classes.
     *
     * @param uc_class Class to check.
     * @return True if the student is in class, false otherwise.
     */
    bool isInClass(const UcClass& uc_class) const;

    /**
     * @brief Checks if the user is enrolled in the specified UC.
     * Complexity: O(n), where n is the number of the student's classes.
     *
     * @param uc_code Code of the UC
     * @return True if the student is registered in the UC, false otherwise.
     */
    bool isInUc(const std::string& uc_code) const;

    /**
     * @brief Returns the lessons of the student.
     * These are obtained from the student's classes.
     * Complexity: O(n), where n is the total number of lessons.
     *
     * @return Vector of the lessons.
     */
    std::vector<Lesson> getLessons() const;

    /**
     * @brief Returns the lessons of the student, ignoring the specified class.
     * These are obtained from the rest of the student's classes.
     * Complexity: O(n), where n is the total number of lessons.
     *
     * @return Vector of the lessons.
     */
    std::vector<Lesson> getLessonsIgnoring(const UcClass& class_to_ignore) const;

    /**
     * @brief Returns the student's admission year.
     * Complexity: O(1)
     *
     * @return Admission year.
     */
    int getAdmissionYear() const;

    /**
     * @brief Returns the student's academic year.
     * Complexity: O(n), where n is the number of classes the student is enrolled in.
     *
     * @return Academic year.
     */
    int getAcademicYear() const;

    /**
     * @brief Returns whether one of the student classes is incompatible with the specified.
     * Complexity: O(n), where n is the number of lessons of the student.
     *
     * @param lesson Lesson to check incompatibility.
     * @return True if the lesson is incompatible with the student's schedule, false otherwise.
     */
    bool lessonsIncompatibleWith(const Lesson& lesson) const;

    /**
     * @brief Returns whether one of the student classes is incompatible with the specified, ignoring a specific class.
     * Complexity: O(n), where n is the number of lessons of the student (except from the class to ignore)
     *
     * @param lesson Lesson to check incompatibility
     * @param class_to_ignore Class to ignore
     * @return True if the lesson is incompatible with the rest of the student's schedule, false otherwise.
     */
    bool lessonsIncompatibleWith(const Lesson& lesson, const UcClass& class_to_ignore) const;

    /**
     * @brief Returns if the first student has a smaller code than the second.
     *
     * @param student Student to compare
     * @return True if the first's code is less than the second's, false otherwise.
     */
    bool operator<(const Student &student) const;
};

/**
 * @brief Reference to a student in the database.
 */
typedef std::set<Student>::iterator StudentRef;

#endif //FEUP_AED1_STUDENT_H