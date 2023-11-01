#ifndef FEUP_AED1_DATASET_H
#define FEUP_AED1_DATASET_H
#include <set>
#include <map>
#include "Student.h"
#include "UcClass.h"

/**
 * @brief Class that stores all dataset information and performs all actions on it.
 */
class Dataset {
public:
    /**
     * @brief Constructs a Dataset instance.
     * @author Diogo Vieira
     */
    Dataset();
    const std::set<Student>& getStudents() const;
    const std::vector<UcClass>& getUcClasses() const;

    /**
     * @brief Reads data files and populates the dataset.
     * @author Diogo Vieira and Bruno Oliveira
     */
    void readFiles();

    /**
     * @brief Reads Uc data from a file and populates the dataset.
     * @author Diogo Vieira
     */
    void readUcs();

    /**
     * @brief Reads UcClasses data from a file and populates the dataset.
     * @author Diogo Vieira
     */
    void readClasses();

    /**
     * @brief Find a specific UcClass based on its unique code and class code.
     *
     * @param uc_code The unique code of the UcClass to find.
     * @param code_of_class The class code of the UcClass to find.
     * @return The found UcClass, or an empty one if not found.
     * @author Bruno Oliveira
     */
    std::vector<UcClass>::iterator findUcClass(const std::string& uc_code, const std::string& code_of_class);

    /**
     * @brief Searches for students in the dataset based on their admission year.
     *
     * @param year The year to search for in student registration codes.
     * @return A vector of students whose admission year matches the specified year.
     * @author Diogo Viera
     */
    std::vector<Student> searchStudentsByAdmissionYear(int year) const;

    /**
     * @brief Searches for students in the dataset who are enrolled in a specific UC class.
     *
     * @param uc_class The UC class to search for.
     * @return A vector of students who are enrolled in the specified UC class.
     * @author Diogo Vieira
     */
    std::vector<Student> searchStudentsByUcClass(const UcClass& uc_class) const;

    /**
     * @brief Searches for students in the dataset who are enrolled in at least 'n' UCs.
     *
     * @param n The minimum number of UCs a student must be enrolled in to be included in the result.
     * @return A vector of students who are enrolled in at least 'n' UCs.
     * @author Diogo Vieira
     */
    std::vector<Student> searchStudentsInAtLeastNUCs(int n) const;

    /**
     * @brief Searches for a student in the dataset by their student code.
     *
     * @param student_code The student code to search for.
     * @return A vector containing the found student(s) with the given code, which may be empty if no student matches the code.
     * @author Diogo Vieira and Bruno Oliveira
     */
    std::set<Student>::iterator searchStudentByCode(int student_code) const;

    /**
     * @brief Searches for students enrolled in a specific UC by its unique code.
     *
     * @param uc_code The unique code of the UC to search for.
     * @return A vector containing the students enrolled in the specified UC, which may be empty if no students are found.
     * @author Diogo Vieira and Bruno Oliveira
     */
    std::vector<Student> searchStudentsInUC(const std::string& uc_code) const;

    /**
     * @brief Searches for students enrolled in a specific class by its class code.
     *
     * @param classCode The code of the class to search for.
     * @return A vector containing the students enrolled in the specified class, which may be empty if no students are found.
     * @author Diogo Vieira
     */
    std::vector<Student> searchStudentsInClass(const std::string& class_code) const;

    /**
     * @brief Reads student data from a file and populates the dataset.
     * @author João Mendes
     */
    void readStudents();

    /**
     * @brief Returns the lessons of the student, based on its classes and sorted by start time.
     * Complexity: O(m*n), where m is the number of classes of the student and n is the max number of lessons in each class.
     * @param student The student for whom to retrieve lessons.
     * @return Student's lessons.
     * @author Diogo Vieira
     */
    std::vector<Lesson> getStudentLessons(const Student& student) const;

    /**
     * @brief Get all UcClasses associated with a specific class code.
     * @param class_code The class code for which to retrieve UcClasses.
     * @return A vector of UcClasses associated with the specified class code.
     * @author Diogo Vieira
     */
    std::vector<UcClass> getUcClassesByClassCode(const std::string& class_code) const;

    /**
     * @brief Searches for students in the dataset based on their academic year.
     * @param year The academic year to search for in student registration codes.
     * @return A vector of students whose academic year matches the specified year.
     * @author Diogo Vieira and Bruno Oliveira
     */
    std::vector<Student> searchStudentsByAcademicYear(int year) const;


private:
    std::vector<UcClass> uc_classes_;
    std::set<Student> students_;
};

#endif //FEUP_AED1_DATASET_H
