/**
 * @file Dataset.h
 * Header file for class Dataset.
 */

#ifndef FEUP_AED1_DATASET_H
#define FEUP_AED1_DATASET_H

#include <set>
#include <map>
#include <map>
#include <queue>
#include <stack>
#include "Student.h"
#include "UcClass.h"
#include "Request.h"

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

    std::set<Student>& getStudents();
    const std::set<Student>& getStudents() const;
    std::vector<UcClass>& getUcClasses();
    const std::vector<UcClass>& getUcClasses() const;
    std::queue<Request>& getPendentRequests();
    const std::queue<Request>& getPendentRequests() const;
    std::stack<Request>& getArchivedRequests();
    const std::stack<Request>& getArchivedRequests() const;

    /**
     * @brief Reads data files and populates the dataset.
     * @author Diogo Vieira and Bruno Oliveira
     */
    void readUcs();

    /**
     * @brief Reads Uc data from a file and populates the dataset.
     * @author Diogo Vieira
     */
    void readClasses();

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
     */
    UcClassRef findUcClass(const std::string& uc_code, const std::string& code_of_class);
    UcClassConstRef findUcClass(const std::string& uc_code, const std::string& code_of_class) const;

    /**
     * @brief Searches for students in the dataset based on their admission year.
     *
     * @param year The year to search for in student registration codes.
     * @return A vector of students whose admission year matches the specified year.
     */
    std::vector<Student> searchStudentsByAdmissionYear(int year) const;

    /**
     * @brief Searches for students in the dataset who are enrolled in a specific UC class.
     *
     * @param uc_class The UC class to search for.
     * @return A vector of students who are enrolled in the specified UC class.
     */
    std::vector<Student> searchStudentsByUcClass(const UcClass& uc_class) const;

    /**
     * @brief Searches for students in the dataset who are enrolled in at least 'n' UCs.
     *
     * @param n The minimum number of UCs a student must be enrolled in to be included in the result.
     * @return A vector of students who are enrolled in at least 'n' UCs.
     */
    std::vector<Student> searchStudentsInAtLeastNUCs(int n) const;

    /**
     * @brief Searches for a student in the dataset by their student code.
     *
     * @param student_code The student code to search for.
     * @return A vector containing the found student(s) with the given code, which may be empty if no student matches the code.
     */
    StudentRef searchStudentByCode(int student_code) const;

    /**
     * @brief Searches for students enrolled in a specific UC by its unique code.
     *
     * @param uc_code The unique code of the UC to search for.
     * @return A vector containing the students enrolled in the specified UC, which may be empty if no students are found.
     */
    std::vector<Student> searchStudentsInUC(const std::string& uc_code) const;

    /**
     * @brief Searches for students enrolled in a specific class by its class code.
     *
     * @param classCode The code of the class to search for.
     * @return A vector containing the students enrolled in the specified class, which may be empty if no students are found.
     */
    std::vector<Student> searchStudentsInClass(const std::string& class_code) const;

    void readStudents();

    void perform(const Request& request);
    bool canAdd(const Request& request, std::string& message) const;
    bool canRemove(const Request& request, std::string& message) const;
    bool canSwitch(const Request& request, std::string& message) const;
    void addUcClass(const Request& request, int student_code);
    void removeUcClass(const Request& request, int student_code);
    bool addBalanceDisturbance(const UcClass& uc_class) const;
    bool removeBalanceDisturbance(const UcClass& uc_class) const;
    bool switchBalanceDisturbance(const UcClass& from, const UcClass& dest, std::string& problem_uc_code) const;
    void saveChangesToFile() const;

    bool isClassFull(const UcClass& uc_class) const;
    std::vector<UcClassConstRef> getClassesInUc(const std::string& uc_code) const;
    std::vector<UcClassRef> getClassesInUc(const std::string& uc_code);

    void saveChanges();


    /**
     * @brief Returns the lessons of the student, based on its classes and sorted by start time.
     * Complexity: O(m*n), where m is the number of classes of the student and n is the max number of lessons
     * in each class
     * @param student
     * @return Student's lessons
     */
    std::vector<Lesson> getStudentLessons(const Student& student) const;

    std::vector<UcClassConstRef> getUcClassesByClassCode(const std::string& class_code) const;
    std::vector<UcClassRef> getUcClassesByClassCode(const std::string& class_code);
    std::vector<std::string> getUcCodes() const;
    std::vector<UcClassConstRef> getClassesByUcCode(const std::string& uc_code) const;
    std::vector<UcClassRef> getClassesByUcCode(const std::string& uc_code);
    std::vector<std::string> getClassCodesByYear(int year) const;

private:
    std::vector<UcClass> uc_classes_;
    std::set<Student> students_;
    std::queue<Request> pendent_requests_;
    std::stack<Request> archived_requests_;
    int max_class_capacity_;
};

#endif //FEUP_AED1_DATASET_H
