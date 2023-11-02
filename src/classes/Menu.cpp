#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>
#include <unordered_map>
#include <cmath>
#include <algorithm>

#include "Menu.h"
#include "Request.h"
#include "Student.h"

using namespace std;

Menu::Menu(Dataset& dataset) : dataset_(dataset) {}

void Menu::launch() {
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

void Menu::requestMenu() {
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

    string uc_code;
    StudentRef student;
    UcClassRef current_class = dataset_.findUcClass("", "");
    UcClassRef target_class = dataset_.findUcClass("", "");
    Request::Type type;
    int student_code;
    int option = receiveOption(NUM_OPTIONS);
    switch (option) {
        case Option::ADD:
            type = Request::ADD;
            student = receiveStudentCode();
            if (student == dataset_.getStudents().end())
                return;
            student_code = student->getStudentCode();
            uc_code = chooseUcMenu();
            target_class = chooseClassMenu(uc_code);
            cout << "\nRequest submitted sucessfully. ";
            waitForEnter();
            break;
        case Option::REMOVE:
            type = Request::REMOVE;
            student = receiveStudentCode();
            if (student == dataset_.getStudents().end())
                return;
            student_code = student->getStudentCode();
            current_class = chooseStudentClassMenu(*student);
            cout << "\nRequest submitted sucessfully. ";
            waitForEnter();
            break;
        case Option::SWITCH:
            type = Request::SWITCH;
            student = receiveStudentCode();
            if (student == dataset_.getStudents().end())
                return;
            student_code = student->getStudentCode();
            current_class = chooseStudentClassMenu(*student);
            uc_code = chooseUcMenu();
            target_class = chooseClassMenu(uc_code);
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

void Menu::saveMenu() {
    queue<Request>& pendent_requests = dataset_.getPendentRequests();
    if (pendent_requests.empty()) {
        cout << "\nNo requests were made\n" << endl;
        return;
    }

    while (!pendent_requests.empty()) {
        performRequest(pendent_requests.front());
        pendent_requests.pop();
    }
    dataset_.saveChangesToFile();
    waitForEnter();
}

void Menu::performRequest(const Request& request) {
    int student_code = request.getStudentCode();
    Student student = *dataset_.searchStudentByCode(student_code);
    string message, problem_uc_code;
    switch (request.getType()) {
        case Request::ADD:
            if (dataset_.canAdd(request, message)) {
                cout << "Adding student name " << student.getStudentName() << " to class " <<
                     request.getTargetClass()->getUcCode() << '-' << request.getTargetClass()->getClassCode() << endl;
                if (dataset_.addBalanceDisturbance(*request.getTargetClass())) {
                    cout << "This will cause imbalance in UC " << request.getTargetClass()->getUcCode() << ". ";
                    if (!confirm())
                        return;
                }
                dataset_.addUcClass(request, student_code);
            } else {
                cout << "Student named " << student.getStudentName() << " failed to enter class "
                     << request.getTargetClass()->getUcCode() << '-' << request.getTargetClass()->getClassCode() << ": "
                     << message << endl;
            }
            break;
        case Request::REMOVE:
            if (dataset_.canRemove(request, message)) {
                cout << "Removing student named " << student.getStudentName() << " from class " <<
                     request.getCurrentClass()->getUcCode() << '-' << request.getCurrentClass()->getClassCode() << endl;
                if (dataset_.removeBalanceDisturbance(*request.getCurrentClass())) {
                    cout << "This will cause imbalance in UC " << request.getCurrentClass()->getUcCode() << ". ";
                    if (!confirm())
                        return;
                }
                dataset_.removeUcClass(request, student_code);
            } else {
                cout << "Student named " << student.getStudentName() << " failed to leave class "
                     << request.getCurrentClass()->getUcCode() << '-' << request.getCurrentClass()->getClassCode() << ": "
                     << message << endl;
            }
            break;
        case Request::SWITCH:
            if (dataset_.canSwitch(request, message)) {
                cout << "Switching student named " << student.getStudentName() << " from class " <<
                     request.getCurrentClass()->getUcCode() << '-' << request.getCurrentClass()->getClassCode() <<
                     " to class " << request.getTargetClass()->getUcCode() << '-'
                     << request.getTargetClass()->getClassCode() << endl;
                if (dataset_.switchBalanceDisturbance(*request.getCurrentClass(), *request.getTargetClass(), problem_uc_code)) {
                    cout << "This will cause imbalance in UC " << request.getTargetClass()->getUcCode() << ". ";
                    if (!confirm())
                        return;
                }

                dataset_.removeUcClass(request, student_code);
                dataset_.addUcClass(request, student_code);
            } else {
                cout << "Student named " << student.getStudentName() << " failed to go from class "
                     << request.getCurrentClass()->getUcCode() << '-' << request.getCurrentClass()->getClassCode()
                     << " to class " << request.getTargetClass()->getUcCode() << '-'
                     << request.getTargetClass()->getClassCode() << ": " << message << endl;
            }
            break;
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

StudentRef Menu::receiveStudentCode() const {
    int code;
    cout << "Please enter the student's code (press q to quit): ";
    while (!(cin >> code)) {
        cin.clear();
        if (getchar() == 'q')
            return dataset_.getStudents().end();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid student code. Please enter another student code (press q to quit): ";
    }

    StudentRef studentRef = dataset_.searchStudentByCode(code);
    if (studentRef == dataset_.getStudents().end()) {
        cout << "Student could not be found. ";
        waitForEnter();
    }
    return studentRef;
}

void Menu::chooseScheduleMenu() const {
    const static string CHOOSE_SCHEDULE_FILEPATH = "src/menus/choose_schedule_menu.txt";
    const static int NUM_OPTIONS = 4;
    enum Option {
        STUDENT_DIAGRAM = 1,
        STUDENT_VISUAL = 2,
        CLASS_DIAGRAM = 3,
        CLASS_VISUAL = 4,
    };

    clearScreen();
    ifstream chooseScheduleFile(CHOOSE_SCHEDULE_FILEPATH);
    if (chooseScheduleFile.fail()) {
        ostringstream error_msg;
        error_msg << "cannot read menu file \"" << CHOOSE_SCHEDULE_FILEPATH << "\".";
        throw ios_base::failure(error_msg.str());
    }

    cout << chooseScheduleFile.rdbuf();

    StudentRef student;
    switch (receiveOption(NUM_OPTIONS)) {
        case Option::STUDENT_DIAGRAM:
            student = receiveStudentCode();
            if (student == dataset_.getStudents().end())
                return;
            displayDiagramSchedule(*student);
            break;
        case Option::STUDENT_VISUAL:
            student = receiveStudentCode();
            if (student == dataset_.getStudents().end())
                return;
            displayVisualSchedule(*student);
            break;
        case Option::CLASS_DIAGRAM:
            displayDiagramSchedule(chooseClassWithYearMenu());
            break;
        case Option::CLASS_VISUAL:
            displayVisualSchedule(chooseClassWithYearMenu());
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
         << " │  " << left << setw(85) << "Class: " + class_code << "│\n"
         << " │                                                                                       │\n";
    for (UcClassConstRef uc_class: dataset_.getUcClassesByClassCode(class_code)) {
        cout << " │  " << left << setw(85) << uc_class->getUcCode() + ":" << "│\n";
        for (const Lesson& lesson: uc_class->getLessons()) {
            ostringstream lesson_str;
            lesson_str << WEEKDAY_TO_STR.at(lesson.getWeekday())
                       << ' ' << lesson.getFormattedStart()
                       << '-' << lesson.getFormattedEnd()
                       << ' ' << TYPE_TO_STR.at(lesson.getType());
            cout << " │    - " << left << setw(81) << lesson_str.str() << "│\n";
        }
        cout << " │                                                                                       │\n";
    }
    cout << " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";
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


    for (UcClassConstRef uc_class: student.getUcClasses()) {
        cout << " │  " << left << setw(85) << uc_class->getUcCode() + " - " + uc_class->getClassCode() + ":" << "│\n";
        for (const Lesson& lesson: uc_class->getLessons()) {
            ostringstream lesson_str;
            lesson_str << WEEKDAY_TO_STR.at(lesson.getWeekday())
                       << ' ' << lesson.getFormattedStart()
                       << '-' << lesson.getFormattedEnd()
                       << ' ' << TYPE_TO_STR.at(lesson.getType());
            cout << " │    - " << left << setw(81) << lesson_str.str() << "│\n";
        }
        cout << " │                                                                                       │\n";
    }
    cout << " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    waitForEnter();
}

string centerFill(const string &str, int width) {
    double space = max((width - (double)str.size()) / 2.0, 0.0);
    return string(ceil(space), ' ') + str + string(floor(space), ' ');
}

void Menu::displayVisualSchedule(const string &class_code) const {
    static const unordered_map<Lesson::Type, string> TYPE_TO_STR = {
            {Lesson::T, "T"}, {Lesson::TP, "TP"}, {Lesson::PL, "PL"}
    };
    static const int NUM_COLUMNS = 6;
    static const int NUM_ROWS = 24;

    vector<vector<string>> schedule_cells(NUM_ROWS, vector<string>(NUM_COLUMNS, ""));
    for (UcClassConstRef uc_class: dataset_.getUcClassesByClassCode(class_code)) {
        for (const Lesson& lesson: uc_class->getLessons()) {
            int column = lesson.getWeekday();
            int start = (int)(lesson.getStart() * 2.0) - 16, end = (int)(lesson.getEnd() * 2.0) - 16;
            for (int row = start; row < end; row++) {
                schedule_cells[row][column] = uc_class->getUcCode() + " (" + TYPE_TO_STR.at(lesson.getType()) + ')';
            }
        }
    }

    clearScreen();
    cout << '\n'
         << " ┌─ Class visual schedule ───────────────────────────────────────────────────────────────────────────────────────────────┐\n"
         << " │                                                                                                                       │\n"
         << " │  Class: " << left << setw(110) << class_code << "│\n"
         << " │                                                                                                                       │\n"
         << " │ ┌─────────────┬────────────────┬────────────────┬────────────────┬────────────────┬────────────────┬────────────────┐ │\n"
         << " │ │     Hour    │     Monday     │     Tuesday    │    Wednesday   │    Thursday    │     Friday     │    Saturday    │ │\n"
         << " │ ├─────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤ │\n";
    double time = 8.0;
    for (int i = 0; i < NUM_ROWS; i++) {
        cout << " │ │" << centerFill(Lesson::formatTime(time) + '-' + Lesson::formatTime(time + 0.5), 13) << "│";
        for (int j = 0; j < NUM_COLUMNS; j++) {
            if (i == 0 || schedule_cells[i][j].empty() || schedule_cells[i - 1][j] != schedule_cells[i][j])
                cout << centerFill(schedule_cells[i][j], 16) << "│";
            else
                cout << "                │";
        }
        cout << " │\n";

        if (i < NUM_ROWS - 1) {
            cout << " │ ├─────────────";
            if (schedule_cells[i][0].empty() || schedule_cells[i][0] != schedule_cells[i + 1][0])
                cout << "┼";
            else
                cout << "┤";
            for (int j = 0; j < NUM_COLUMNS; j++) {
                if (schedule_cells[i][j].empty() || schedule_cells[i][j] != schedule_cells[i + 1][j]) {
                    cout << "────────────────";
                    if (j < NUM_COLUMNS - 1
                        && (schedule_cells[i][j + 1].empty() || schedule_cells[i][j + 1] != schedule_cells[i + 1][j + 1]))
                        cout << "┼";
                    else
                        cout << "┤";
                } else {
                    cout << "                ";
                    if (j < NUM_COLUMNS - 1
                        && (schedule_cells[i][j + 1].empty() || schedule_cells[i][j + 1] != schedule_cells[i + 1][j + 1]))
                        cout << "├";
                    else
                        cout << "│";
                }
            }
            cout << " │\n";
        } else {
            cout << " │ └─────────────┴────────────────┴────────────────┴────────────────┴────────────────┴────────────────┴────────────────┘ │\n"
                 << " └───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n\n";
        }
        time += 0.5;
    }
    waitForEnter();
}

void Menu::displayVisualSchedule(const Student &student) const {
    static const unordered_map<Lesson::Type, string> TYPE_TO_STR = {
            {Lesson::T, "T"}, {Lesson::TP, "TP"}, {Lesson::PL, "PL"}
    };
    static const int NUM_COLUMNS = 6;
    static const int NUM_ROWS = 24;

    vector<vector<string>> schedule_cells(NUM_ROWS, vector<string>(NUM_COLUMNS, ""));
    for (UcClassConstRef uc_class: student.getUcClasses()) {
        for (const Lesson& lesson: uc_class->getLessons()) {
            int column = lesson.getWeekday();
            int start = (int)(lesson.getStart() * 2.0) - 16, end = (int)(lesson.getEnd() * 2.0) - 16;
            for (int row = start; row < end; row++) {
                schedule_cells[row][column] = uc_class->getUcCode() + " (" + TYPE_TO_STR.at(lesson.getType()) + ')';
            }
        }
    }

    clearScreen();
    cout << '\n'
         << " ┌─ Student visual schedule ─────────────────────────────────────────────────────────────────────────────────────────────┐\n"
         << " │                                                                                                                       │\n"
         << " │  Student code: " << left << setw(103) << student.getStudentCode() << "│\n"
         << " │  Student name: " << setw(103) << student.getStudentName() << "│\n"
         << " │                                                                                                                       │\n"
         << " │ ┌─────────────┬────────────────┬────────────────┬────────────────┬────────────────┬────────────────┬────────────────┐ │\n"
         << " │ │     Hour    │     Monday     │     Tuesday    │    Wednesday   │    Thursday    │     Friday     │    Saturday    │ │\n"
         << " │ ├─────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤ │\n";
    double time = 8.0;
    for (int i = 0; i < NUM_ROWS; i++) {
        cout << " │ │" << centerFill(Lesson::formatTime(time) + '-' + Lesson::formatTime(time + 0.5), 13) << "│";
        for (int j = 0; j < NUM_COLUMNS; j++) {
            if (i == 0 || schedule_cells[i][j].empty() || schedule_cells[i - 1][j] != schedule_cells[i][j])
                cout << centerFill(schedule_cells[i][j], 16) << "│";
            else
                cout << "                │";
        }
        cout << " │\n";

        if (i < NUM_ROWS - 1) {
            cout << " │ ├─────────────";
            if (schedule_cells[i][0].empty() || schedule_cells[i][0] != schedule_cells[i + 1][0])
                cout << "┼";
            else
                cout << "┤";
            for (int j = 0; j < NUM_COLUMNS; j++) {
                if (schedule_cells[i][j].empty() || schedule_cells[i][j] != schedule_cells[i + 1][j]) {
                    cout << "────────────────";
                    if (j < NUM_COLUMNS - 1
                        && (schedule_cells[i][j + 1].empty() || schedule_cells[i][j + 1] != schedule_cells[i + 1][j + 1]))
                        cout << "┼";
                    else
                        cout << "┤";
                } else {
                    cout << "                ";
                    if (j < NUM_COLUMNS - 1
                        && (schedule_cells[i][j + 1].empty() || schedule_cells[i][j + 1] != schedule_cells[i + 1][j + 1]))
                        cout << "├";
                    else
                        cout << "│";
                }
            }
            cout << " │\n";
        } else {
            cout << " │ └─────────────┴────────────────┴────────────────┴────────────────┴────────────────┴────────────────┴────────────────┘ │\n"
                 << " └───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n\n";
        }
        time += 0.5;
    }
    waitForEnter();
}

UcClassRef Menu::chooseStudentClassMenu(const Student& student) {
    clearScreen();
    cout << '\n'
         << " ┌─ Choose the student class ────────────────────────────────────────────────────────────┐\n"
         << " │                                                                                       │\n"
         << " │  Options:                                                                             │\n";
    list<UcClassConstRef> classes = student.getUcClasses();
    int i = 1;
    for (auto it = classes.begin(); it != classes.end(); it++) {
        ostringstream option_str;
        option_str << '[' << i << "] " << (*it)->getUcCode() << '-' << (*it)->getClassCode();
        cout << " │    " << left << setw(83) << option_str.str() << "│\n";
        i++;
    }
    cout << " │                                                                                       │\n"
         << " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    auto it = classes.begin();
    for (i = receiveOption((int)classes.size()); i > 1; i++)
        it++;
    vector<UcClass>& uc_classes = dataset_.getUcClasses();
    return equal_range(uc_classes.begin(), uc_classes.end(), **it).first;
}

string Menu::chooseUcMenu() const {
    clearScreen();
    cout << '\n'
         << " ┌─ Choose an UC ────────────────────────────────────────────────────────────────────────┐\n"
         << " │                                                                                       │\n"
         << " │  Options:                                                                             │\n";
    vector<string> uc_codes = dataset_.getUcCodes();
    for (int i = 0; i < uc_codes.size(); i++) {
        ostringstream option_str;
        option_str << '[' << i + 1 << "] " << uc_codes[i];
        cout << " │    " << left << setw(83) << option_str.str() << "│\n";
    }
    cout << " │                                                                                       │\n"
         << " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    return uc_codes[receiveOption((int)uc_codes.size()) - 1];
}

UcClassConstRef Menu::chooseClassMenu(const string& uc_code) const {
    clearScreen();
    cout << '\n'
         << " ┌─ Choose a class ──────────────────────────────────────────────────────────────────────┐\n"
         << " │                                                                                       │\n"
         << " │  Options:                                                                             │\n";
    vector<UcClassRef> classes = dataset_.getClassesByUcCode(uc_code);
    for (int i = 0; i < classes.size(); i++) {
        ostringstream option_str;
        option_str << '[' << i + 1 << "] " << classes[i]->getClassCode();
        cout << " │    " << left << setw(83) << option_str.str() << "│\n";
    }
    cout << " │                                                                                       │\n"
         << " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    return classes[receiveOption((int)classes.size()) - 1];
}

UcClassRef Menu::chooseClassMenu(const string& uc_code) {
    clearScreen();
    cout << '\n'
         << " ┌─ Choose a class ──────────────────────────────────────────────────────────────────────┐\n"
         << " │                                                                                       │\n"
         << " │  Options:                                                                             │\n";
    vector<UcClassRef> classes = dataset_.getClassesByUcCode(uc_code);
    for (int i = 0; i < classes.size(); i++) {
        ostringstream option_str;
        option_str << '[' << i + 1 << "] " << classes[i]->getClassCode();
        cout << " │    " << left << setw(83) << option_str.str() << "│\n";
    }
    cout << " │                                                                                       │\n"
         << " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    return classes[receiveOption((int)classes.size()) - 1];
}

string Menu::chooseClassWithYearMenu() const {
    int year;
    vector<string> class_codes;
    cout << "Please insert the year: ";
    while (true) {
        if (!(cin >> year)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid year. Please insert a year: ";
            continue;
        }

        class_codes = dataset_.getClassCodesByYear(year);
        if (class_codes.empty()) {
            cout << "No classes for this year were found. Please insert another year: ";
            continue;
        }

        break;
    }

    clearScreen();
    cout << '\n'
         << " ┌─ Choose a class ──────────────────────────────────────────────────────────────────────┐\n"
         << " │                                                                                       │\n"
         << " │  Options:                                                                             │\n";
    for (int i = 0; i < class_codes.size(); i++) {
        ostringstream option_str;
        option_str << '[' << i + 1 << "] " << class_codes[i];
        cout << " │    " << left << setw(83) << option_str.str() << "│\n";
    }
    cout << " │                                                                                       │\n"
         << " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";

    return class_codes[receiveOption((int)class_codes.size()) - 1];
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

bool Menu::confirm() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Proceed? [Y/N]: ";
    return toupper(getchar()) == 'Y';
}

void Menu::waitForEnter() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Press ENTER to continue...";
    getchar();
}

void Menu::clearScreen() {
    system("clear || cls");
}