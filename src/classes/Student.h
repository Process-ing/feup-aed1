/**
 * Header file for class Student.
 */

#ifndef FEUP_AED1_STUDENT_H
#define FEUP_AED1_STUDENT_H
#include <list>
#include <string>


class Student {
private:
    int StudentCode_;
    std::string StudentName_;
    std::list<std::string> UcClasses_;
public:
    /**
     * @brief Constructor of the class.
     * @author João Mendes
     * @param StudentCode Represents the student's code.
     * @param StudentName Represents the student's name.
     */
    Student(int StudentCode, std::string StudentName);


    int getStudentCode() const;
    std::string getStudentName() const;
    std::list<std::string> &getUcClasses();
    const std::list<std::string> &getUcClasses() const;
};

#endif //FEUP_AED1_STUDENT_H