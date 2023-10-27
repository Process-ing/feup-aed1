//
// Created by bruno on 10/20/23.
//

#ifndef FEUP_AED1_DATASET_H
#define FEUP_AED1_DATASET_H

#include <set>

#include "Student.h"
#include "UcClass.h"

/**
 * @brief Class that stores all dataset information and performs all actions on it.
 */
class Dataset {
  public:
    Dataset();

    const std::set<Student>& getStudents() const;
    const std::set<UcClass>& getUcClasses() const;

  private:
    std::set<Student> students;
    std::set<UcClass> ucClasses;
};


#endif //FEUP_AED1_DATASET_H
