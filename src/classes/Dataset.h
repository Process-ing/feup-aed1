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

    /**
     * Reads Uc data from a file and populates the dataset.
     */
    void UcReader();

    /**
     * Reads UcClasses data from a file and populates the dataset.
     */
    void UcClassReader();

    /**
     * Find a specific UcClass based on its unique code and class code.
     *
     * @param uc_code The unique code of the UcClass to find.
     * @param code_of_class The class code of the UcClass to find.
     * @return The found UcClass, or an empty one if not found.
     */
    UcClass findUcClass(const std::string& uc_code, const std::string& code_of_class);

    /**
     * Searches for students in the dataset based on their admission year.
     *
     * @param year The year to search for in student registration codes.
     * @return A vector of students whose admission year matches the specified year.
     */
    std::vector<Student> searchStudentsByAdmissionYear(int year) const;

    /**
     * Searches for students in the dataset who are enrolled in a specific UC class.
     *
     * @param uc_class The UC class to search for.
     * @return A vector of students who are enrolled in the specified UC class.
     */
    std::vector<Student> searchStudentsByUcClass(const UcClass& uc_class) const;

    /**
     * Searches for students in the dataset who are enrolled in at least 'n' UCs.
     *
     * @param n The minimum number of UCs a student must be enrolled in to be included in the result.
     * @return A vector of students who are enrolled in at least 'n' UCs.
     */
    std::vector<Student> searchStudentsInAtLeastNUCs(int n) const;

    /**
     * Searches for a student in the dataset by their student code.
     *
     * @param student_code The student code to search for.
     * @return A vector containing the found student(s) with the given code, which may be empty if no student matches the code.
     */
    std::vector<Student> searchStudentsByCode(int student_code) const;

    /**
     * Searches for students enrolled in a specific UC by its unique code.
     *
     * @param uc_code The unique code of the UC to search for.
     * @return A vector containing the students enrolled in the specified UC, which may be empty if no students are found.
     */
    std::vector<Student> searchStudentsInUC(const std::string& uc_code) const;

    /**
     * Searches for students enrolled in a specific class by its class code.
     *
     * @param classCode The code of the class to search for.
     * @return A vector containing the students enrolled in the specified class, which may be empty if no students are found.
     */
    std::vector<Student> searchStudentsInClass(const std::string& class_code) const;

private:
    std::set<Student> students_;
    std::set<UcClass> uc_classes_;
};

#endif //FEUP_AED1_DATASET_H