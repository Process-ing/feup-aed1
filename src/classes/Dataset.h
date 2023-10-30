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
        const vector<UcClass>& getAllClasses() const;
        const std::set<Student>& getStudents() const;
        const std::set<UcClass>& getUcClasses() const;
        /**
         * Reads Uc data from a file and populates the dataset.
         * @author Diogo Vieira
         */
        void UcReader();

        /**
         * Reads UcClasses data from a file and populates the dataset.
         * @author Diogo Vieira
         */
        void UcClassReader();

        /**
         * Find a specific UcClass based on its unique code and class code.
         *
         * @param uc_code The unique code of the UcClass to find.
         * @param code_of_class The class code of the UcClass to find.
         * @return The found UcClass, or an empty one if not found.
         * @author Diogo Vieira
         */
        UcClass findUcClass(string uc_code, string code_of_class);
        /**
        * @brief Searches for students in the dataset based on their registration year.
        * @param year The year to search for in student registration codes.
        * @return A vector of students whose registration year matches the specified year.
        * @author Diogo Vieira
        */
        vector<Student> searchStudentsByYear(int year) const;
        vector<Student> searchStudentsByClass(string ucclass_code) const;
    private:
        std::set<Student> students;
        std::set<UcClass> ucClasses;
        vector<UcClass> all_classes;

};

#endif //FEUP_AED1_DATASET_H
