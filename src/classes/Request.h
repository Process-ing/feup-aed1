/**
 * @file Request.h
 * Header file for class Request.
 */

#ifndef FEUP_AED1_REQUEST_H
#define FEUP_AED1_REQUEST_H

#include <string>

#include "UcClass.h"
#include "Student.h"

/**
 * @brief Class abstraction for requests for addition, removal and exchange of students' classes.
 */
class Request {
public:

    /**
     * @brief Type of request
     * @details The possible values are ADD - to add a student to the target class -, REMOVE - to remove a student off
     * the target class -, and SWITCH - to change a student to the target class, removing him from its respective class.
     */
    enum Type {
        ADD,
        REMOVE,
        SWITCH,
    };

    Request(Type type, int student_code, UcClassRef current_class, UcClassRef target_class);

    Type getType() const;
    int getStudentCode() const;
    UcClassRef getCurrentClass() const;
    UcClassRef getTargetClass() const;

private:
    Type type_;
    int student_code_;
    UcClassRef current_class_;
    UcClassRef target_class_;
};


#endif //FEUP_AED1_REQUEST_H