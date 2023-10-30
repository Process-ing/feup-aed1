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
        * @brief Searches for students in the dataset based on their admission year.
        * @param year The year to search for in student registration codes.
        * @return A vector of students whose admission year matches the specified year.
        * @author Diogo Vieira
        */
        vector<Student> searchStudentsByAdmissionYear(int year) const;
        /**
        * @brief Searches for students in the dataset who are enrolled in a specific UC class.
        * @param ucclass The UC class to search for.
        * @return A vector of students who are enrolled in the specified UC class.
        * @author Diogo Vieira
        */
        vector<Student> searchStudentsByUcClass(UcClass& uc_class) const;
        /**
        * @brief Searches for students in the dataset who are enrolled in at least 'n' UCs.
        * @param n The minimum number of UCs a student must be enrolled in to be included in the result.
        * @return A vector of students who are enrolled in at least 'n' UCs.
        * @author Diogo Vieira
        */
        vector<Student> searchStudentsInAtLeastNUCs(int n) const;
        /**
        * @brief Searches for a student in the dataset by their student code.
        * @param student_code The student code to search for.
        * @return A vector containing the found student(s) with the given code, which may be empty if no student matches the code.
        * @author Diogo Vieira
        */
        vector<Student> searchStudentsByCode(int student_code) const;
        /**
        * @brief Searches for students enrolled in a specific UC by its unique code.
        * @param uc_code The unique code of the UC to search for.
        * @return A vector containing the students enrolled in the specified UC, which may be empty if no students are found.
        * @author Diogo Vieira
        */
        vector<Student> searchStudentsInUC(string uc_code) const;
        /**
        * @brief Searches for students enrolled in a specific class by its class code.
        * @param classCode The code of the class to search for.
        * @return A vector containing the students enrolled in the specified class, which may be empty if no students are found.
        * @author Diogo Vieira
        */
        vector<Student> searchStudentsInClass(string code_of_class) const;
    private:
        std::set<Student> students;
        std::set<UcClass> ucClasses;
        vector<UcClass> all_classes;
};

#endif //FEUP_AED1_DATASET_H
