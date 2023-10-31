#ifndef FEUP_AED1_REQUEST_H
#define FEUP_AED1_REQUEST_H

#include <string>

#include "UcClass.h"
#include "Dataset.h"
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
        SWITCH
    };

    Request(Type type, Student& student, UcClass& current_class, UcClass& target_class);

    void perform(Dataset& dataset);

    Type getType() const;
    const Student& getStudent() const;
    const UcClass& getTargetClass() const;
    bool alreadyInUc(UcClass* what_class);
    // bool classFull();
    bool addBalanceDisturbance(Dataset &dataset);
    bool removeBalanceDisturbance(Dataset &dataset);
    bool overlaping();

  private:
    Type type_;
    Student* student_;
    UcClass* current_class_;
    UcClass* target_class_;
};


#endif //FEUP_AED1_REQUEST_H
