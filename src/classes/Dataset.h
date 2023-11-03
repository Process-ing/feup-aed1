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
     * @brief Constructs a Dataset instance and populates it by reading the dataset files.
     */
    Dataset();

    /**
     * @brief Returns all the students.
     * Complexity: O(1)
     *
     * @return Set with the students in the system.
     */
    const std::set<Student>& getStudents() const;

    /**
     * @brief Returns all the UcClasses in the dataset.
     * Complexity: O(1)
     *
     * @return Sorted vector of UcClass objects.
     */
    const std::vector<UcClass>& getUcClasses() const;

    /**
     * @brief Returns the oldest pending request and removes it from the system.
     * Complexity: O(1)
     *
     * @return The oldest pending request.
     */
    Request popPendentRequest();

    /**
     * @brief Adds a new request to the queue of pending requests.
     * Complexity: O(1)
     *
     * @param request The request to add.
     */
    void pushPendentRequest(const Request& request);

    /**
     * @brief Returns all pending requests in the system.
     * Complexity: O(1)
     *
     * @return Queue with pending requests.
     */
    const std::queue<Request>& getPendentRequests() const;

    /**
     * @brief Returns the most recent archived request and removes it from the system.
     * Complexity: O(1)
     *
     * @return The newest archived request.
     */
    Request popArchivedRequest();

    /**
     * @brief Adds the request to the stack of archived requests.
     * Complexity: O(1)
     *
     * @param request Request to add.
     */
    void pushArchivedRequest(const Request& request);

    /**
     * @brief Returns all the archived request in the system.
     * Complexity: O(1)
     *
     * @return Deque with all the archived requests.
     */
    const std::deque<Request>& getArchivedRequests() const;

    /**
     * @brief Returns the max capacity of all classes.
     * Complexity: O(1)
     *
     * @return The max capacity
     */
    int getMaxClassCapacity() const;

    /**
     * @brief Reads the Uc data from the files and populates the dataset.
     * It will fail if the file "dataset/classes_per_uc.csv" cannot be found.
     * Complexity: O(n), where n is the number of lines read in the file.
     */
    void readUcs();

    /**
     * @brief Reads the class data from the files and populates the dataset.
     * It will fail if the file "dataset/classes.csv cannot be found. It should only be executed after readUcs().
     * Complexity: O(n*(log(m)+log(k))), where n is the total number of lessons read, m is the number of UcClass objects
     * in the system and k is the maximum number of lessons of each class.
     */
    void readClasses();

    /**
     * @brief Reads the student data from the files and populates the dataset.
     * It will fail if the file "dataset/student_classes.csv cannot be found. It should only be executed after
     * readClasses().
     * Complexity: O(n*log(n)+m*log(k)), where n is the number of students read, m is the number of lines read in the
     * file and k is the number of UcClass objects in the dataset.
     */
    void readStudents();

    /**
     * @brief Reads the archived request from the files and puts them in the dataset.
     * It should only be executed after readStudents().
     * Complexity: O(n*log(m)), where n is the number of lines read in the file and m is the number of UcClass objects
     * in the dataset.
     */
    void readArchive();

    /**
     * @brief Find a specific UcClass based on its uc code and class code.
     * Complexity: O(log(n)), where n is the number of UcClass objects.
     *
     * @param uc_code The code of the respective UC.
     * @param class_code The code of the class.
     * @return A reference to the UcClass, if one is found, and getUcClasses().end() otherwise.
     */
    UcClassRef findUcClass(const std::string& uc_code, const std::string& class_code);

    /**
     * @brief Find a specific UcClass based on its uc code and class code.
     * Complexity: O(log(n)), where n is the number of UcClass objects.
     *
     * @param uc_code The code of the respective UC.
     * @param class_code The code of the class.
     * @return A constant reference to the UcClass, if one is found, and getUcClasses().end() otherwise.
     */
    UcClassConstRef findUcClass(const std::string& uc_code, const std::string& class_code) const;

    /**
     * @brief Searches for students in the dataset based on their admission year.
     * Complexity: O(log(n)+m), where n is the total number of students in the database and m is the number of students
     * found.
     *
     * @param year The admission year.
     * @return Sorted vector of students whose admission year matches the specified year.
     */
    std::vector<Student> searchStudentsByAdmissionYear(int year) const;

    /**
     * @brief Searches for students in the dataset who are enrolled in the specific UcClass.
     * Complexity: O(n*m), where n is the number of students in the dataset and m is the maximum number of student
     * classes.
     *
     * @param uc_class The UC class to search for.
     * @return Sorted vector of students who are enrolled in the specified UC class.
     */
    std::vector<Student> searchStudentsByUcClass(const UcClass& uc_class) const;

    /**
     * @brief Searches for students in the dataset who are enrolled in at least the number of UCs specified.
     * Complexity: O(n), where n is the number of students in the dataset.
     *
     * @param n The minimum number of UCs.
     * @return Sorted vector of students who are enrolled in at least n UCs.
     */
    std::vector<Student> searchStudentsInAtLeastNUCs(int n) const;

    /**
     * @brief Searches for a student in the dataset by their student code.
     * Complexity: O(log(n)), where n is the number of students in the dataset,
     *
     * @param student_code The student code.
     * @return Reference to the wanted student, or getStudents().end() if it does not find one.
     */
    StudentRef searchStudentByCode(int student_code) const;

    /**
     * @brief Searches for students enrolled in a specific UC by its unique code.
     * Complexity: O(n*m), where n is the number of students in the dataset and m is the maximum number of classes a
     * student has.
     *
     * @param uc_code The unique code of the UC to search for.
     * @return Sorted vector containing the students enrolled in the specified UC, which may be empty if no students are found.
     */
    std::vector<Student> searchStudentsInUC(const std::string& uc_code) const;

    /**
     * @brief Searches for students enrolled in a specific class by its class code.
     * Complexity: O(n*m), where n is the number of students in the dataset and m is the maximum number of classes a
     * student has.
     *
     * @param classCode The code of the class to search for.
     * @return Sorted vector containing the students enrolled in the specified class, which may be empty if no students are found.
     */
    std::vector<Student> searchStudentsInClass(const std::string& class_code) const;

    /**
     * @brief Returns all unique class codes.
     * Complexity: O(n*log(m)), where n is the number of UcClass objects in the dataset and m is the number of unique
     * class codes.
     *
     * @return Vector with the class codes.
     */
    std::vector<std::string> getAllClassCodes() const;

    /**
     * @brief Returns all the classes in the UC.
     * Complexity: O(log(n)+m), where n is the number of UcClass objects in the dataset and m is the number of UcClass
     * objects found.
     *
     * @param uc_code Code of the UC.
     * @return Vector with the classes.
     */
    std::vector<UcClassConstRef> getClassesInUc(const std::string& uc_code) const;

    /**
     * @brief Returns all the classes in the UC.
     * Complexity: O(log(n)+m), where n is the number of UcClass objets in the dataset and m is the number of UcClass
     * objects found.
     *
     * @param uc_code Code of the UC.
     * @return Vector with the classes.
     */
    std::vector<UcClassRef> getClassesInUc(const std::string& uc_code);

    /**
     * @brief Searches for students in the dataset based on their academic year.
     * Complexity: O(n*m), where n is the number of students in the dataset and m is the maximum number of classes a
     * student is enrolled in.
     *
     * @param year The academic year.
     * @return Sorted vector of all students int the specified academic year.
     */
    std::vector<Student> searchStudentsByAcademicYear(int year) const;

    /**
     * @brief Searches all the classes with the specified class code.
     * Complexity: O(n), where n is the number of UcClass objects in the dataset.
     *
     * @param class_code Class code.
     * @return Vector with the references to the classes fetched.
     */
    std::vector<UcClassConstRef> getUcClassesByClassCode(const std::string& class_code) const;

    /**
     * @brief Searches all the classes with the specified class code.
     * Complexity: O(n), where n is the number of UcClass objects in the dataset.
     *
     * @param class_code Class code.
     * @return Vector with the references to the UcClasses fetched.
     */
    std::vector<UcClassRef> getUcClassesByClassCode(const std::string& class_code);

    /**
     * @brief Returns the codes of all UCs.
     * Complexity: O(n), where n is the number of UcClass objects in the dataset.
     *
     * @return Sorted vector with all UC codes.
     */
    std::vector<std::string> getUcCodes() const;

    /**
     * @brief Searches the classes in the specified UC.
     * Complexity: O(log(n)+m), where n is the number of UcClass objects in the dataset and m is the number of objects
     * fetched.
     *
     * @param uc_code Code of the UC.
     * @return Vector with references to the UcClasses in the UC.
     */
    std::vector<UcClassConstRef> getClassesByUcCode(const std::string& uc_code) const;

    /**
     * @brief Searches the classes in the specified UC.
     * Complexity: O(log(n)+m), where n is the number of UcClass objects in the dataset and m is the number of objects
     * fetched.
     *
     * @param uc_code Code of the UC.
     * @return Vector with references to the UcClasses in the UC.
     */
    std::vector<UcClassRef> getClassesByUcCode(const std::string& uc_code);

    /**
     * @brief Returns all the class codes of all classes of the specified academic year.
     * Complexity: O(n*log(m)), where n is the number of UcClass objects in the dataset and m the number of uc codes
     * obtained.
     *
     * @param year Academic year.
     * @return Vector with the uc codes.
     */
    std::vector<std::string> getClassCodesByYear(int year) const;

    /**
     * @brief Returns if the class is full or not.
     * Complexity: O(1)
     *
     * @param uc_class Class to check
     * @return True if is full, false otherwise
     */
    bool isClassFull(const UcClass& uc_class) const;

    /**
     * @brief Returns whether the add request can be executed or not.
     * Complexity: O(log(n)+m*k), where n is the number of students in the dataset, m is the number of lessons the
     * request's target class has and k the number of lessons the request's student has.
     *
     * @param request Request to check.
     * @param message Message about why the request cannot be done, if that's the case
     * @return True if the request can be performed, false otherwise
     */
    bool canAdd(const Request& request, std::string& message) const;

    /**
     * @brief Returns whether the remove request can be executed or not.
     * Complexity: O(log(n)+m), where n is the number of students and m the number of classes the request's student has.
     *
     * @param request Request to check.
     * @param message Message about why the request cannot be done, if that's the case
     * @return True if the request can be performed, false otherwise
     */
    bool canRemove(const Request& request, std::string& message) const;

    /**
     * @brief Returns whether the switch request can be executed or not.
     * Complexity: O(log(n)+m*k), where n is the number of students in the dataset, m is the number of lessons the
     * request's target class has and k the number of lessons the request's student has.
     *
     * @param request Request to check.
     * @param message Message about why the request cannot be done, if that's the case
     * @return True if the request can be performed, false otherwise
     */
    bool canSwitch(const Request& request, std::string& message) const;

    /**
     * @brief Places a student on the specified class.
     * Complexity: O(log(n)), where n is the number of students in the dataset.
     *
     * @param uc_class Class to add to student.
     * @param student_code Student code of the student.
     */
    void addUcClass(UcClassRef uc_class, int student_code);

    /**
     * @brief Removes a student from the specified class.
     * Complexity: O(log(n)+m), where n is the number of students in the dataset and m is the number of classes the
     * request's student has.
     *
     * @param uc_class Class to remove from student.
     * @param student_code Student code of the student.
     */
    void removeUcClass(UcClassRef uc_class, int student_code);

    /**
     * @brief Checks if adding a student to the class will disturb the UC balance.
     * Complexity: O(log(n)+m), where n is the number of UcClass objects in the dataset and m is the number of classes
     * in the UC of the class.
     *
     * @param uc_class Class to add
     * @return True if there will be disturbance, false otherwise
     */
    bool addBalanceDisturbance(const UcClass& uc_class) const;

    /**
     * @brief Checks if removing a student from the class will disturb the UC balance.
     * Complexity: O(log(n)+m), where n is the number of UcClass objects in the dataset and m is the number of classes
     * in the UC of the class.
     *
     * @param uc_class Class to remove
     * @return True if there will be disturbance, false otherwise
     */
    bool removeBalanceDisturbance(const UcClass& uc_class) const;

    /**
     * @brief Checks if switching a student from a class to the other will disturb one of the UCs balance.
     * Complexity: O(log(n)+m+k), where n is the number of UcClass objects in the dataset, m is the number of classes
     * in the UC of from class and k the number of classes in the UC of dest class.
     *
     * @param from Current class.
     * @param dest Class to go to.
     * @param problem_uc_code Uc code of the UC what will be unbalanced, if any
     * @return True if there will be disturbance, false otherwise
     */
    bool switchBalanceDisturbance(const UcClass& from, const UcClass& dest, std::string& problem_uc_code) const;

    /**
     * @brief Saves the changes (on the students and the archived requests) to the files.
     * Complexity: O(n*m+k), where n is the number of students in the dataset, m is the maximum number of classes a
     * student has and k is the number of requests in the archive.
     */
    void saveChangesToFile();

    /**
     * @brief Returns whether the database has unsaved changes or not.
     * Complexity: O(1)
     *
     * @return True if there are unsaved changes, false otherwise.
     */
    bool hasUnsavedChanges() const;

private:
    std::vector<UcClass> uc_classes_;
    std::set<Student> students_;
    std::queue<Request> pendent_requests_;
    std::deque<Request> request_archive_;
    int max_class_capacity_;
    bool has_unsaved_changes_;
};

#endif //FEUP_AED1_DATASET_H
