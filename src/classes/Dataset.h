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
    /**
     * @brief Default constructor.
     * @author Bruno Oliveira
     */
    Dataset();

    /**
     * @brief Returns a set with all the students in the dataset.
     * @author Bruno Oliveira
     *
     * @return Set of students
     */
    const std::set<Student>& getStudents();

    /**
     * @brief Returns a set with all uc classes in the dataset.
     * @author Bruno Oliveira
     *
     * @return Set of uc classes
     */
    const std::set<UcClass>& getUcClasses();

  private:
    std::set<Student> students;
    std::set<UcClass> ucClasses;
};


#endif //FEUP_AED1_DATASET_H
