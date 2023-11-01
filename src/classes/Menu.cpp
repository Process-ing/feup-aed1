#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>

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
        cout << welcome_screen_file.rdbuf();

        switch (receiveOption(NUM_OPTIONS)) {
            case Option::SEARCH:
                searchMenu();
                break;
            case Option::EXIT:
                cout << "Exiting the app. ";
                waitForEnter();
                return;
            case Option::SCHEDULE:
                break;
            case Option::REQUEST:
                break;
            case Option::SAVE:
                cout << "Saved all changes. ";
                waitForEnter();
                break;
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
        case Option::ALL_STUDENTS:{
            set<Student> all_students_set = dataset_.getStudents();
            vector<Student> all_students(all_students_set.begin(), all_students_set.end());
            sortStudents(sortMenu(), all_students);
            displayStudentsNameAndCode(all_students);
            break;
        }
        case Option::ALL_UCS: {
            displayUcs();
            break;
        }

        case Option::ALL_CLASSES: {
            displayClasses();
            break;
        }
        case Option::STUDENT_CODE: {
            searchStudentByCode();
            break;
        }
        case Option::STUDENTS_UC: {
            searchStudentByUc();
            break;
        }
        case Option::STUDENTS_CLASS: {
            searchStudentsByClass();
            break;
        }
        case Option::STUDENTS_UC_CLASS:{
            searchStudentsInUcClass();
            break;
        }
        case Option::STUDENTS_ADMISSION_YEAR: {
            searchStudentsByAdmissionYear();
            break;
        }
        case Option::STUDENTS_ACADEMIC_YEAR:{
            searchStudentsByAcademicYear();
            break;
        }
        case Option::STUDENTS_N_UCS: {
            searchStudentInAtLeastNUcs();
            break;
        }
        case Option::GO_BACK:
            return;
    }
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
    getchar();
}

void Menu::sortStudents(Menu::SortOption sortingOption, vector<Student>& students) const {
    const static int NUM_OPTIONS = 4;
    switch (sortingOption) {
        case SortOption::ALPHABETICAL_ORDER:
            sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
                return a.getStudentName() < b.getStudentName();
            });
            break;
        case SortOption::REVERSE_ALPHABETICAL_ORDER:
            sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
                return a.getStudentName() > b.getStudentName();
            });
            break;
        case SortOption::ASCENDING_CODES:
            sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
                return a.getStudentCode() < b.getStudentCode();
            });
            break;
        case SortOption::DESCENDING_CODES:
            sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
                return a.getStudentCode() > b.getStudentCode();
            });
            break;
    }
}


void Menu::searchStudentByCode() const {
    int student_code;
    cout << "Enter the student code: ";
    cin >> student_code;
    const std::set<Student>& students = dataset_.getStudents();
    auto student_by_code = students.find(Student(student_code, ""));
    if (student_by_code != students.end()) {
        displayStudent(*student_by_code);
    }
}

void Menu::searchStudentByUc() const {
    string uc_code;
    cout << "Enter the UC code: ";
    cin >> uc_code;
    vector<Student> students_in_uc = dataset_.searchStudentsInUC(uc_code);
    sortStudents(sortMenu(), students_in_uc);
    displayStudentsNameAndCode(students_in_uc);
}

void Menu::searchStudentsByClass() const {
    string class_code;
    cout << "Enter the class code: ";
    cin >> class_code;
    vector<Student> students_in_class = dataset_.searchStudentsInClass(class_code);
    sortStudents(sortMenu(), students_in_class);
    displayStudentsNameAndCode(students_in_class);
}

void Menu::searchStudentInAtLeastNUcs() const {
    int n;
    cout << "Enter the minimum number of UCs: ";
    cin >> n;
    vector<Student> students_in_at_least_n_ucs = dataset_.searchStudentsInAtLeastNUCs(n);
    sortStudents(sortMenu(), students_in_at_least_n_ucs);
    displayStudentsNameAndCode(students_in_at_least_n_ucs);
}

void Menu::searchStudentsByAdmissionYear() const {
    int year;
    cout << "Enter the admission year: ";
    cin >> year;
    vector<Student> students_by_year = dataset_.searchStudentsByAdmissionYear(year);
    sortStudents(sortMenu(), students_by_year);
    displayStudentsNameAndCode(students_by_year);
}

void Menu::searchStudentsByAcademicYear() const{
    int year;
    cout << "Enter the academic year: ";
    cin >> year;
    vector<Student> students_by_academic_year = dataset_.searchStudentsByAcademicYear(year);
    sortStudents(sortMenu(), students_by_academic_year);
    displayStudentsNameAndCode(students_by_academic_year);
}

void Menu::searchStudentsInUcClass() const {
    string uc_code, class_code;
    cout << "Enter the UC code: ";
    cin >> uc_code;
    cout << "Enter the class code: ";
    cin >> class_code;
    UcClass uc_class(uc_code, class_code);
    vector<Student> students_in_ucclass = dataset_.searchStudentsByUcClass(uc_class);
    sortStudents(sortMenu(), students_in_ucclass);
    displayStudentsNameAndCode(students_in_ucclass);
}

void Menu::displayStudent(const Student student) const {
    cout << "-----------------" << endl;
    cout << "Student Name: " << student.getStudentName() << endl;
    cout << "Student Code: " << student.getStudentCode() << endl;
    cout << "-----------------" << endl;
}

void Menu::displayStudentsNameAndCode(const vector<Student>& students) const {
    if (students.empty()) {
        return;
    }
    int max_results = 10;
    int page = 0;
    int total_pages = (students.size() + max_results - 1) / max_results;

    while (page < total_pages) {
        cout << "Page " << (page + 1) << " of " << total_pages << ":" << endl;
        cout << "-----------------" << endl;

        for (int i = page * max_results; i < min((page + 1) * max_results, static_cast<int>(students.size())); i++) {
            const Student &student = students[i];
            cout << "Student Name: " << student.getStudentName() << endl;
            cout << "Student Code: " << student.getStudentCode() << endl;
            cout << "-----------------" << endl;
        }

        if (page < total_pages - 1) {
            cout << "[1] Next page" << endl;
        }

        if (page > 0) {
            cout << "[2] Previous page" << endl;
        }

        cout << "[3] Go back" << endl;
        cout << "_________________________" << endl;
        cout << "Choose an option: ";

        int option;
        cin >> option;

        if (option == 1 && page < total_pages - 1) {
            page++;
        } else if (option == 2 && page > 0) {
            page--;
        } else if (option == 3) {
            break;
        }
        cin.ignore();
    }
}

void Menu::displayUcs() const {
    if (dataset_.getUcClasses().empty()) {
        cout << "No UC classes found." << endl;
        return;
    }
    cout << "List of UC Classes:" << endl;
    cout << "-----------------" << endl;
    string prev_uc_code;
    for (const UcClass& uc_class : dataset_.getUcClasses()) {
        if (uc_class.getUcCode() != prev_uc_code) {
            cout << "UC Code: " << uc_class.getUcCode() << endl;
            cout << "-----------------" << endl;
            prev_uc_code = uc_class.getUcCode();
        }
    }
}

void Menu::displayClasses() const {
    if (dataset_.getUcClasses().empty()) {
        cout << "No classes found." << endl;
        return;
    }
    cout << "List of Classes:" << endl;
    cout << "-----------------" << endl;

    string prev_uc_class;

    for (const UcClass& ucClass : dataset_.getUcClasses()) {
        if (ucClass.getClassCode() != prev_uc_class) {
            cout << "Class Code: " << ucClass.getClassCode() << endl;
            cout << "-----------------" << endl;
            prev_uc_class = ucClass.getClassCode();
        }

    }
}