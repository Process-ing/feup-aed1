/**
 * @file Menu.h
 * Header file for class Menu
 */

#ifndef FEUP_AED1_MENU_H
#define FEUP_AED1_MENU_H

#include <vector>
#include <string>
#include "Dataset.h"

/**
 * @brief The Menu class handles the user interface and interactions with the dataset.
 */
class Menu {
  public:
    /**
     * @brief Constructs a Menu instance.
     * @param dataset The dataset used by the menu.
     * @author Bruno Oliveira
     */
    explicit Menu(Dataset& dataset);

    /**
     * @brief Launches the menu, starting with the welcome screen.
     * @author Bruno Oliviera
     */
    void launch();

    /**
     * @brief Searches for a student by their code.
     * @author Diogo Vieira
     */
    void searchStudentByCode() const;

    /**
     * @brief Searches for students enrolled in a specific UC.
     * @author Diogo Vieira and Bruno Oliveira
     */
    void searchStudentByUc() const;

    /**
     * @brief Searches for students in a specific class.
     * @author Diogo Vieira
     */
    void searchStudentsByClass() const;

    /**
     * @brief Searches for students enrolled in at least a given number of UCs.
     * @author Diogo Vieira
     */
    void searchStudentInAtLeastNUcs() const;

    /**
     * @brief Searches for students admitted in a specific academic year.
     * @author Diogo Vieira
     */
    void searchStudentsByAdmissionYear() const;

    /**
     * @brief Searches for students enrolled in a specific UC class.
     * @author Diogo Vieira
     */
    void searchStudentsInUcClass() const;

    /**
     * @brief Searches for students in a specific academic year.
     * @author Bruno Oliveira
     */
    void searchStudentsByAcademicYear() const;

    /**
     * @brief Displays the list of UCs.
     * @author Diogo Vieira and Bruno Oliveira
     */
    void displayUcs() const;

    /**
     * @brief Displays the list of classes.
     * @author Diogo Vieira
     */
    void displayClasses() const;

    /**
     * @brief Displays the names and codes of students.
     * @param students The list of students to display.
     * @author Diogo Vieira
     */
    void displayStudentsNameAndCode(const std::vector<Student> &students) const;

    /**
     * @brief Sorts the list of students based on the provided sorting option.
     * @param sortingOption The sorting option to apply.
     * @param students The list of students to sort.
     * @author Diogo Vieira
     */

    /**
     * @brief Displays information about a single student.
     * @param student The student to display.
     * @author Diogo Vieira
     */
    void displayStudent(const Student& student) const;
    void displayStudents() const;
    void displayClassesInUc() const;

private:
    /**
     * @brief Reference to the dataset used by the menu.
     * @author Bruno Oliveira
     */
    Dataset &dataset_;

    /**
     * @brief Displays the main search menu.
     * @author Bruno Oliveira
     */
    void searchMenu() const;
    void requestMenu();
    void saveMenu();
    void performRequest(const Request& request);

    /**
     * @brief Displays a menu for sorting options and returns the chosen option.
     * @return The selected sorting option.
     * @author Diogo Vieira and Bruno Oliveira
     */
    static void sortMenu(std::vector<Student>& students);
    void chooseScheduleMenu() const;
    void displayDiagramSchedule(const std::string& class_code) const;
    void displayDiagramSchedule(const Student& student) const;
    void displayVisualSchedule(const std::string& class_code) const;
    void displayVisualSchedule(const Student& student) const;
    std::string chooseUcMenu() const;
    UcClassConstRef chooseClassMenu(const std::string& uc_code) const;
    UcClassRef chooseClassMenu(const std::string& uc_code);
    std::string chooseClassWithYearMenu() const;
    UcClassRef chooseStudentClassMenu(const Student& student);
    void displayClassOccupation(const std::string& uc_code) const;

    StudentRef receiveStudentCode() const;
    /**
     * @brief Receives an option from the user, validating it against a maximum value.
     * @param max The maximum valid option.
     * @return The user's chosen option.
     * @author Bruno Oliveira
     */
    static int receiveOption(int max);
    static bool confirm();

    /**
     * @brief Waits for the user to press Enter before continuing.
     * @author Bruno Oliveira
     */
    static void waitForEnter();
    static void clearScreen();
};

#endif //FEUP_AED1_MENU_H
