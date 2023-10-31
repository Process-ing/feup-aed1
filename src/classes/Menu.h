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
     */
    explicit Menu(Dataset& dataset);

    /**
     * @brief Enumerates sorting options for student lists.
     */
    enum SortOption {
        ALPHABETICAL_ORDER = 1,
        REVERSE_ALPHABETICAL_ORDER = 2,
        ASCENDING_CODES = 3,
        DESCENDING_CODES = 4,
    };

    /**
     * @brief Launches the menu, starting with the welcome screen.
     */
    void launch() const;

    /**
     * @brief Searches for a student by their code.
     * @author Diogo Vieira
     */
    void searchStudentByCode() const;

    /**
     * @brief Searches for students enrolled in a specific UC.
     * @author Diogo Vieira
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
     * @author Diogo Vieira and Bruno Oliveira
     */
    void searchStudentsByAcademicYear() const;

    /**
     * @brief Displays the list of UCs.
     * @author Diogo Vieira
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
    void sortStudents(SortOption sortingOption, std::vector<Student> &students) const;

private:
    /**
     * @brief Reference to the dataset used by the menu.
     */
    Dataset &dataset_;

    /**
     * @brief Displays the main search menu.
     */
    void searchMenu() const;

    /**
     * @brief Displays a menu for sorting options and returns the chosen option.
     * @return The selected sorting option.
     */
    static SortOption sortMenu();

    /**
     * @brief Receives an option from the user, validating it against a maximum value.
     * @param max The maximum valid option.
     * @return The user's chosen option.
     */
    static int receiveOption(int max);

    /**
     * @brief Waits for the user to press Enter before continuing.
     */
    static void waitForEnter();
};

#endif //FEUP_AED1_MENU_H