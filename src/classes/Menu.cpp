#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>
#include <unordered_map>

#include "Menu.h"

using namespace std;

Menu::Menu(Dataset& dataset) : dataset_(dataset) {}

void Menu::launch() const {
    const static string WELCOME_SCREEN_FILEPATH = "src/menus/welcome_screen.txt";
    const static int NUM_OPTIONS = 5;
    enum Option {
        SEARCH = 1,
        SCHEDULE = 2,
        REQUEST = 3,
        SAVE = 4,
        EXIT = 5,
    };

    ifstream welcome_screen_file(WELCOME_SCREEN_FILEPATH);
    if (welcome_screen_file.fail()) {
        ostringstream error_msg;
        error_msg << "cannot read menu file \"" << WELCOME_SCREEN_FILEPATH << "\".";
        throw ios_base::failure(error_msg.str());
    }

    while (true) {
        clearScreen();
        cout << welcome_screen_file.rdbuf();

        switch (receiveOption(NUM_OPTIONS)) {
            case Option::SEARCH:
                searchMenu();
                break;
            case Option::SCHEDULE:
                chooseScheduleMenu();
                break;
            case Option::EXIT:
                cout << "Exiting the app. ";
                waitForEnter();
                return;
        }

        welcome_screen_file.seekg(0);
    }
}

void Menu::searchMenu() const {
    const static string SEARCH_MENU_FILEPATH = "src/menus/search_menu.txt";
    const static int NUM_OPTIONS = 11;
    enum Option {
        ALL_STUDENTS = 1,
        ALL_UCS = 2,
        ALL_CLASSES = 3,
        STUDENT_CODE = 4,
        STUDENTS_UC = 5,
        STUDENTS_CLASS = 6,
        STUDENTS_UC_CLASS = 7,
        STUDENTS_ACADEMIC_YEAR = 8,
        STUDENTS_ADMISSION_YEAR = 9,
        STUDENTS_N_UCS = 10,
        GO_BACK = 11,
    };

    clearScreen();
    ifstream search_menu_file(SEARCH_MENU_FILEPATH);
    if (search_menu_file.fail()) {
        ostringstream error_msg;
        error_msg << "cannot read menu file \"" << SEARCH_MENU_FILEPATH << "\".";
        throw ios_base::failure(error_msg.str());
    }

    cout << search_menu_file.rdbuf();

    switch (receiveOption(NUM_OPTIONS)) {
        case Option::ALL_STUDENTS:
            sortMenu();
        case Option::GO_BACK:
            return;
    }
}

Menu::SortOption Menu::sortMenu() {
    const static string SORT_MENU_FILEPATH = "src/menus/sort_menu.txt";
    const static int NUM_OPTIONS = 4;

    clearScreen();
    ifstream sort_menu_file(SORT_MENU_FILEPATH);
    if (sort_menu_file.fail()) {
        ostringstream error_msg;
        error_msg << "cannot read menu file \"" << SORT_MENU_FILEPATH << "\".";
        throw ios_base::failure(error_msg.str());
    }

    cout << sort_menu_file.rdbuf();
    return (SortOption) receiveOption(NUM_OPTIONS);
}

void Menu::chooseScheduleMenu() const {
    const static string CHOOSE_SCHEDULE_FILEPATH = "src/menus/choose_schedule_menu.txt";
    const static int NUM_OPTIONS = 2;
    enum Option {
        STUDENT = 1,
        CLASS = 2,
    };

    clearScreen();
    ifstream chooseScheduleFile(CHOOSE_SCHEDULE_FILEPATH);
    if (chooseScheduleFile.fail()) {
        ostringstream error_msg;
        error_msg << "cannot read menu file \"" << CHOOSE_SCHEDULE_FILEPATH << "\".";
        throw ios_base::failure(error_msg.str());
    }

    cout << chooseScheduleFile.rdbuf();

    switch (receiveOption(NUM_OPTIONS)) {
        case Option::STUDENT:
            displayDiagramSchedule(*dataset_.getStudents().begin());
            break;
        case Option::CLASS:
            displayDiagramSchedule("1LEIC01");
    }
}

void Menu::displayDiagramSchedule(const string& class_code) const {
    static const unordered_map<Lesson::Weekday, string> WEEKDAY_TO_STR = {
            {Lesson::MONDAY, "Monday"}, {Lesson::TUESDAY, "Tuesday"}, {Lesson::WEDNESDAY, "Wednesday"},
            {Lesson::THURSDAY, "Thursday"}, {Lesson::FRIDAY, "Friday"}, {Lesson::SATURDAY, "Saturday"}
    };
    static const unordered_map<Lesson::Type, string> TYPE_TO_STR = {
            {Lesson::T, "T"}, {Lesson::TP, "TP"}, {Lesson::PL, "PL"}
    };

    clearScreen();
    cout << '\n'
         << " ┌─ Class diagram schedule ──────────────────────────────────────────────────────────────┐\n"
         << " │                                                                                       │\n"
         << " |  " << left << setw(85) << "Class: " + class_code << "|\n"
         << " │                                                                                       │\n";
    for (const UcClass& uc_class: dataset_.getUcClassesByClassCode(class_code)) {
        cout << " │  " << left << setw(85) << uc_class.getUcCode() + ":" << "│\n";
        for (const Lesson& lesson: uc_class.getLessons()) {
            ostringstream lesson_str;
            lesson_str << "Weekday: " << WEEKDAY_TO_STR.at(lesson.getWeekday())
                << "; Start: " << lesson.getFormattedStart()
                << "; End: " << lesson.getFormattedEnd()
                << "; Type: " << TYPE_TO_STR.at(lesson.getType());
            cout << " |    - " << left << setw(81) << lesson_str.str() << "│\n";
        }
    }

    cout << " │                                                                                       │\n"
         << " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    waitForEnter();
}

void Menu::displayDiagramSchedule(const Student &student) const {
    static const unordered_map<Lesson::Weekday, string> WEEKDAY_TO_STR = {
            {Lesson::MONDAY, "Monday"}, {Lesson::TUESDAY, "Tuesday"}, {Lesson::WEDNESDAY, "Wednesday"},
            {Lesson::THURSDAY, "Thursday"}, {Lesson::FRIDAY, "Friday"}, {Lesson::SATURDAY, "Saturday"}
    };
    static const unordered_map<Lesson::Type, string> TYPE_TO_STR = {
            {Lesson::T, "T"}, {Lesson::TP, "TP"}, {Lesson::PL, "PL"}
    };

    clearScreen();
    cout << '\n'
         << " ┌─ Student diagram schedule ────────────────────────────────────────────────────────────┐\n"
         << " │                                                                                       │\n"
         << " │  " << left << setw(85) << "Student code: " + to_string(student.getStudentCode()) << "│\n"
         << " │  " << setw(85) << "Student name: " + student.getStudentName() << "│\n"
         << " │                                                                                       │\n";


    for (UcClassRef uc_class: student.getUcClasses()) {
        cout << " │  " << left << setw(85) << uc_class->getUcCode() + " - " + uc_class->getClassCode() + ":" << "│\n";
        for (const Lesson& lesson: uc_class->getLessons()) {
            ostringstream lesson_str;
            lesson_str << "Weekday: " << WEEKDAY_TO_STR.at(lesson.getWeekday())
                       << "; Start: " << lesson.getFormattedStart()
                       << "; End: " << lesson.getFormattedEnd()
                       << "; Type: " << TYPE_TO_STR.at(lesson.getType());
            cout << " |    - " << left << setw(81) << lesson_str.str() << "│\n";
        }
    }

    cout << " │                                                                                       │\n"
         << " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    waitForEnter();
}

int Menu::receiveOption(int max) {
    int option;
    cout << "Please choose an option: ";
    while (!(cin >> option) || option <= 0 || option > max) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid option. Please choose another option: ";
    }
    return option;
}

void Menu::waitForEnter() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Press ENTER to continue...";
    getchar();
}

void Menu::clearScreen() {
    system("clear || cls");
}