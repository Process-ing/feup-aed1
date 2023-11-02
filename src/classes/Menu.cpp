#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

#include "Menu.h"
#include "Request.h"
#include "Student.h"

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
        cout << welcome_screen_file.rdbuf();

        switch (receiveOption(NUM_OPTIONS)) {
            case Option::SEARCH:
                searchMenu();
                break;
            case Option::REQUEST:
                requestMenu();
                break;
            case Option::SAVE:
                saveMenu();
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

void Menu::requestMenu() const {
    const static string REQUEST_MENU_FILEPATH = "src/menus/request_menu.txt";
    const static int NUM_OPTIONS = 5;
    enum Option {
        ADD = 1,
        REMOVE = 2,
        SWITCH = 3,
        UNDO = 4,
        GO_BACK = 5,
    };

    ifstream request_menu_file(REQUEST_MENU_FILEPATH);
    if (request_menu_file.fail()) {
        ostringstream error_msg;
        error_msg << "cannot read menu file \"" << REQUEST_MENU_FILEPATH << "\".";
        throw ios_base::failure(error_msg.str());
    }

    cout << request_menu_file.rdbuf();

    string uc_code, class_code;
    UcClassRef current_class = dataset_.findUcClass("", "");
    UcClassRef target_class = dataset_.findUcClass("", "");
    Request::Type type;
    int option = receiveOption(NUM_OPTIONS);
    int student_code;
    switch (option) {
        case Option::ADD:
            type = Request::ADD;
            student_code = receiveStudentCode();
            if (student_code == -1)
                return;
            cout << "Please enter the UC code of the UcClass you want to add: ";
            cin >> uc_code;
            cout << "Please enter the class code of the UcClass you want to add: ";
            cin >> class_code;
            target_class = dataset_.findUcClass(uc_code, class_code);
            cout << "\nRequest submitted sucessfully. ";
            waitForEnter();
            break;
        case Option::REMOVE:
            type = Request::REMOVE;
            student_code = receiveStudentCode();
            if (student_code == -1)
                return;
            cout << "Please enter the UC code of the UcClass you want to remove: ";
            cin >> uc_code;
            cout << "Please enter the class code of the UcClass you want to remove: ";
            cin >> class_code;
            current_class = dataset_.findUcClass(uc_code, class_code);
            cout << "\nRequest submitted sucessfully. ";
            waitForEnter();
            break;
        case Option::SWITCH:
            type = Request::SWITCH;
            student_code = receiveStudentCode();
            if (student_code == -1)
                return;
            cout << "Please enter the UC code of the UcClass you want to go from: ";
            cin >> uc_code;
            cout << "Please enter the class code of the UcClass you want to go from: ";
            cin >> class_code;
            current_class = dataset_.findUcClass(uc_code, class_code);
            cout << "Please enter the UC code of the UcClass you want to go to: ";
            cin >> uc_code;
            cout << "Please enter the class code of the UcClass you want to go to: ";
            cin >> class_code;
            target_class = dataset_.findUcClass(uc_code, class_code);
            cout << "\nRequest submitted sucessfully. ";
            waitForEnter();
            break;
        case Option::UNDO:
            if (dataset_.getArchivedRequests().empty()) {
                cout << "\nNo requests to undo." << endl;
                waitForEnter();
            }
            else {
                Request last = dataset_.getArchivedRequests().top();
                dataset_.getArchivedRequests().pop();
                student_code = last.getStudentCode();
                if (last.getType() == Request::ADD) {
                    type = Request::REMOVE;
                    current_class = last.getTargetClass();
                }
                else if (last.getType() == Request::REMOVE) {
                    type = Request::ADD;
                    target_class = last.getCurrentClass();
                }
                else if (last.getType() == Request::SWITCH) {
                    type = Request::SWITCH;
                    current_class = last.getTargetClass();
                    target_class = last.getCurrentClass();
                }
                cout << "\nUndo was successful." << endl;
            }
            break;
        case Option::GO_BACK:
            return;
    }
    dataset_.getPendentRequests().emplace(type, student_code, current_class, target_class);
    if (option != Option::UNDO)
        dataset_.getArchivedRequests().emplace(type, student_code, current_class, target_class);
}

void Menu::saveMenu() const {
    if (!dataset_.getPendentRequests().empty())
        cout << "\nSaved the following changes:\n";
    dataset_.saveChanges();
    waitForEnter();
}

Menu::SortOption Menu::sortMenu() {
    const static string SORT_MENU_FILEPATH = "src/menus/sort_menu.txt";
    const static int NUM_OPTIONS = 4;

    ifstream sort_menu_file(SORT_MENU_FILEPATH);
    if (sort_menu_file.fail()) {
        ostringstream error_msg;
        error_msg << "cannot read menu file \"" << SORT_MENU_FILEPATH << "\".";
        throw ios_base::failure(error_msg.str());
    }

    cout << sort_menu_file.rdbuf();
    return (SortOption) receiveOption(NUM_OPTIONS);
}

//UcClass Menu::chooseUcClassMenu() const {
//    clearScreen();
//    cout << "┌─ Request ─────────────────────────────────────────────────────────────────────────────┐\n"
//            "│                                                                                       │\n";
//
//}

int Menu::receiveStudentCode() const {
    int code;
    cout << "Please enter the student's code (press q to quit): ";
    while (!(cin >> code)) {
        cin.clear();
        if (getchar() == 'q')
            return -1;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid student code. Please enter another student code (press q to quit): ";
    }

    if (dataset_.searchStudentByCode(code) == dataset_.getStudents().end()) {
        cout << "Student could not be found. ";
        waitForEnter();
        return -1;
    }
    return code;
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