//
// Created by memechanic on 18-10-2023.
//

#ifndef FEUP_AED1_STUDENT_H
#define FEUP_AED1_STUDENT_H
#include "Lesson.h"
#include <list>
#include <string>


class Student {
private:
    int StudentCode_;
    std::string StudentName_;
    std::string UcCode_;
    std::string ClassCode_;
    std::list<Lesson> lessons;
public:
    Student(int StudentCode, std::string StudentName, std::string UcCode, std::string ClassCode);

    int getStudentCode() const;
    std::string getStudentName() const;
    std::string getUcCode() const;
    std::string getClassCode() const;

    void setStudentCode(int StudentCode);
    void setStudentName(std::string StudentName);
    void setUcCode(std::string UcCode);
    void setClassCode(std::string ClassCode);
};

#endif //FEUP_AED1_STUDENT_H