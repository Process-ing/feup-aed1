/**
 * Header file for class Student.
 */

#ifndef FEUP_AED1_STUDENT_H
#define FEUP_AED1_STUDENT_H
#include "UcClass.h"
#include <list>
#include <set>
#include <string>
#include <set>

typedef std::vector<UcClass>::const_iterator UcClassRef;

class Student {
private:
    int student_code_;
    std::string student_name_;
    std::list<UcClassRef> uc_classes_;
    int max_class_capacity_ = 0;
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
    std::list<UcClassRef> &getUcClasses();
    const std::list<UcClassRef> &getUcClasses() const;
    bool hasClass(const UcClass& uc_class) const;
    bool operator<(const Student &student) const;
};

#endif //FEUP_AED1_STUDENT_H