/**
 * @file Window.h
 * Header file for class Window
 */

#ifndef FEUP_AED1_WINDOW_H
#define FEUP_AED1_WINDOW_H

#include <vector>
#include <string>
#include "Dataset.h"

/**
 * @brief The Window class handles the user interface and interactions with the dataset.
 */
class Window {
  public:
    /**
     * @brief Constructs a Window instance.
     * @param dataset The dataset used by the Window.
     */
    explicit Window(Dataset& dataset);

    /**
     * @brief Launches the window, starting with the welcome screen.
     */
    void launch();

  private:
    Dataset &dataset_;

    /**
     * @brief Displays the main search menu.
     */
    void searchMenu() const;

    /**
     * @brief Displays the requests menu.
     */
    void requestMenu();

    /**
     * @brief Performs the pending requests on the database and displays the changes.
     */
    void saveMenu();

    /**
     * @brief Tries to perform the specified request and gives feedback to the user about them.
     * @param request Request to perform
     */
    void performRequest(const Request& request);

    /**
     * @brief Displays a menu to choose the sorting option for the student listings.
     */
    static void sortMenu(std::vector<Student>& students);

    /**
     * @brief Displays the schedule option selection menu.
     */
    void chooseScheduleMenu() const;

    /**
     * @brief Shows the diagram schedule of a class.
     *
     * @param class_code Class code of the class.
     */
    void displayDiagramSchedule(const std::string& class_code) const;

    /**
     * @brief Shows the diagram schedule of a student.
     *
     * @param student Student.
     */
    void displayDiagramSchedule(const Student& student) const;

    /**
     * @brief Shows the visual schedule of a class.
     *
     * @param class_code Class code of the class.
     */
    void displayVisualSchedule(const std::string& class_code) const;

    /**
     * @brief Shows the visual schedule of a student.
     *
     * @param student Student.
     */
    void displayVisualSchedule(const Student& student) const;

    /**
     * @brief Displays a menu to choose an UC.
     *
     * @return The uc code of the UC chosen.
     */
    std::string chooseUcMenu() const;

    /**
     * @brief Displays a menu to choose a class of the specified UC.
     *
     * @param uc_code Code of the UC.
     * @return Reference to the corresponding class
     */
    UcClassConstRef chooseClassMenu(const std::string& uc_code) const;

    /**
     * @brief Displays a menu to choose a class of the specified UC.
     *
     * @param uc_code Code of the UC.
     * @return Reference to the corresponding UcClass
     */
    UcClassRef chooseClassMenu(const std::string& uc_code);

    /**
     * @brief Displays a menu to choose a class from the specified academic year.
     *
     * @return Code of the class chosen
     */
    std::string chooseClassWithYearMenu() const;

    /**
     * @brief Displays a menu to choose a class from the specified student
     *
     * @param student Student
     * @return Reference to the chosen class.
     */
    UcClassRef chooseStudentClassMenu(const Student& student);

    /**
     * @brief Displays the occupation of all classes of the given UC.
     *
     * @param uc_code Code of the UC.
     */
    void displayClassOccupation(const std::string& uc_code) const;

    /**
     * @brief Asks the user for a student code.
     *
     * @return Reference to the chosen student, or a reference to the end of the students of the dataset if the student
     * code does not point to any student or the user chooses to exit.
     */
    StudentRef receiveStudentCode() const;

    /**
     * @brief Receives an option from the user, validating it against a maximum value.
     *
     * @param max The maximum value for a valid option.
     * @return The user's chosen option.
     */
    static int receiveOption(int max);

    /**
     * @brief Asks the user if it wants to proceed with an action.
     *
     * @return True if it chooses to continue, false otherwise.
     */
    static bool confirm();

    /**
     * @brief Waits for the user to press Enter before continuing.
     */
    static void waitForEnter();

    /**
     * @brief Clears the terminal where the program is running.
     */
    static void clearScreen();

    /**
     * @brief Shows the search results for a student by their code.
     */
    void searchStudentByCode() const;

    /**
     * @brief Shows the search results for the students enrolled in a specific UC.
     */
    void searchStudentByUc() const;

    /**
     * @brief Shows the search results for the students in a specific class.
     */
    void searchStudentsByClass() const;

    /**
     * @brief Shows the search results for the students enrolled in at least a given number of UCs.
     */
    void searchStudentInAtLeastNUcs() const;

    /**
     * @brief Shows the search results for the students admitted in a specific year.
     */
    void searchStudentsByAdmissionYear() const;

    /**
     * @brief Shows the search results for the students enrolled in a specific UC and class.
     */
    void searchStudentsInUcClass() const;

    /**
     * @brief Shows the search result for students in a specific academic year.
     */
    void searchStudentsByAcademicYear() const;

    /**
     * @brief Displays the list of all students.
     */
    void displayStudents() const;

    /**
     * @brief Displays the list of all UCs.
     */
    void displayUcs() const;

    /**
     * @brief Displays the list of all classes.
     */
    void displayClasses() const;

    /**
     * @brief Displays the names and codes of the specified students.
     *
     * @param students Vector of students to display.
     */
    void displayStudentsNameAndCode(const std::vector<Student> &students) const;

    /**
     * @brief Displays information (code and name) about a single student.
     *
     * @param student The student to display.
     */
    void displayStudent(const Student& student) const;

    /**
     * @brief Displays the class codes of all classes in the chosen UC.
     */
    void displayClassesInUc() const;

    /**
     * @brief Sends a message to the user about leaving the program.
     * If the system has unsaved changes, it will ask for the student if it wishes to discard them and exit.
     * @return True if the user wants to leave, false otherwise.
     */
    bool leave() const;
};

#endif //FEUP_AED1_WINDOW_H
