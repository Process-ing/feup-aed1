/**
 * Header file for class Student.
 */

#ifndef FEUP_AED1_STUDENT_H
#define FEUP_AED1_STUDENT_H
#include "UcClass.h"
#include <list>
#include <string>


class Student {
private:
    int student_code_;
    std::string student_name_;
    std::list<UcClass*> uc_classes_;
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
    std::list<UcClass*> &getUcClasses();
    const std::list<UcClass*> &getUcClasses() const;
    bool studentClass(string code_of_class) const
};

#endif //FEUP_AED1_STUDENT_H