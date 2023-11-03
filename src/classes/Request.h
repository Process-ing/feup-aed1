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

    /**
     * @brief Constructs a Request instance with the given parameters.
     *
     * @param type Type of request.
     * @param student_code Code of the student to change classes.
     * @param current_class Reference to the original class (irrelevant for ADD requests).
     * @param target_class Reference to the wanted class (irrelevant for REMOVE requests).
     */
    Request(Type type, int student_code, UcClassRef current_class, UcClassRef target_class);

    /**
     * @brief Returns the request type.
     * @return Type of the request.
     */
    Type getType() const;

    /**
     * @brief Returns the code of the student to change classes.
     * @return Student code.
     */
    int getStudentCode() const;

    /**
     * @brief Returns the current class of the student.
     * @return Reference to the current class.
     */
    UcClassRef getCurrentClass() const;

    /**
     * @brief Returns the class that the student wants to join.
     * @return Reference to the class.
     */
    UcClassRef getTargetClass() const;

private:
    Type type_;
    int student_code_;
    UcClassRef current_class_;
    UcClassRef target_class_;
};


#endif //FEUP_AED1_REQUEST_H