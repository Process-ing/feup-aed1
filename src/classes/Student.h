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

class Student {
  private:
    int student_code_;
    std::string student_name_;
    std::list<UcClassConstRef> uc_classes_;

  public:
    /**
     * @brief Constructor of the class.
     * @author João Mendes
     * @param student_code Represents the student's code.
     * @param student_name Represents the student's name.
     */
    Student(int student_code, const std::string &student_name);


    int getStudentCode() const;
    std::string getStudentName() const;
    std::list<UcClassConstRef> &getUcClasses();
    const std::list<UcClassConstRef> &getUcClasses() const;
    bool isInClass(const UcClass& uc_class) const;
    bool isInUc(const std::string& uc_code) const;
    std::vector<Lesson> getLessons() const;
    std::vector<Lesson> getLessonsIgnoring(const UcClass& class_to_ignore) const;
    int getAcademicYear() const;
    bool lessonsOverlapsWith(const Lesson& lesson) const;
    bool lessonsOverlapsWith(const Lesson& lesson, const UcClass& class_to_ignore) const;
    bool operator<(const Student &student) const;
};

typedef std::set<Student>::iterator StudentRef;

#endif //FEUP_AED1_STUDENT_H