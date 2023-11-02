#include "Student.h"
#include "UcClass.h"
#include "Dataset.h"
#include "Lesson.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <list>
#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;

Dataset::Dataset() {
    max_class_capacity_ = 0;
    readUcs();
    readClasses();
    readStudents();
}

std::set<Student> &Dataset::getStudents() {
    return students_;
}

const set<Student>& Dataset::getStudents() const {
    return students_;
}

std::vector<UcClass> &Dataset::getUcClasses() {
    return uc_classes_;
}

const vector<UcClass>& Dataset::getUcClasses() const {
    return uc_classes_;
}

void Dataset::readUcs() {
    static const string CLASSES_PER_UC_FILEPATH = "dataset/classes_per_uc.csv";
    ifstream classes_per_uc_file(CLASSES_PER_UC_FILEPATH);
    if (classes_per_uc_file.fail()) {
        ostringstream error_msg;
        error_msg << "Could not open file \"" << CLASSES_PER_UC_FILEPATH << '"';
        throw ios_base::failure(error_msg.str());
    }
    string line, uc_code, class_code;
    getline(classes_per_uc_file, line);
    while (getline(classes_per_uc_file, uc_code, ',')) {
        getline(classes_per_uc_file, class_code);
        uc_classes_.emplace_back(uc_code, class_code);
    }
    sort(uc_classes_.begin(), uc_classes_.end());
}

void Dataset::readClasses() {
    static const string CLASSES_FILEPATH = "dataset/classes.csv";
    static const unordered_map<string, Lesson::Type> STR_TO_TYPE = {
            { "T", Lesson::T }, { "TP", Lesson::TP }, { "PL", Lesson::PL },
    };
    static const unordered_map<string, Lesson::Weekday> STR_TO_WEEKDAY = {
            {"Monday", Lesson::MONDAY}, {"Tuesday", Lesson::TUESDAY}, {"Wednesday", Lesson::WEDNESDAY},
            {"Thursday", Lesson::THURSDAY}, {"Friday", Lesson::FRIDAY}, {"Saturday", Lesson::SATURDAY}
    };
    ifstream classes_file(CLASSES_FILEPATH);
    if (classes_file.fail()) {
        ostringstream error_msg;
        error_msg << "Could not open the file \"" << CLASSES_FILEPATH << endl;
        throw ios_base::failure(error_msg.str());
    }
    string line, class_code, uc_code, weekday_str, start, duration, type;

    getline(classes_file, line);
    while (getline(classes_file, class_code, ',')) {
        getline(classes_file, uc_code, ',');
        getline(classes_file, weekday_str, ',');
        getline(classes_file, start, ',');
        getline(classes_file, duration, ',');
        getline(classes_file, type);


        Lesson newLesson(
            stod(start),
            stod(duration) + stod(start),
            STR_TO_TYPE.at(type),
            STR_TO_WEEKDAY.at(weekday_str)
        );
        findUcClass(uc_code, class_code)->getLessons().push_back(newLesson);
    }

    for (UcClass& uc_class: uc_classes_) {
        vector<Lesson>& lessons = uc_class.getLessons();
        sort(lessons.begin(), lessons.end());
    }
}

UcClassRef Dataset::findUcClass(const string& uc_code, const string& class_code) {
    return equal_range(uc_classes_.begin(), uc_classes_.end(), UcClass(uc_code, class_code)).first;
}

UcClassConstRef Dataset::findUcClass(const string& uc_code, const string& class_code) const {
    return equal_range(uc_classes_.begin(), uc_classes_.end(), UcClass(uc_code, class_code)).first;
}

vector<Student> Dataset::searchStudentsByAdmissionYear(int year) const {
    vector<Student> res;
    auto it = students_.lower_bound(Student(year * 100000, ""));
    while (it != students_.end() && it->getAdmissionYear() == year) {
        res.push_back(*it);
        it++;
    }
    return res;
}

StudentRef Dataset::searchStudentByCode(int student_code) const {
    return students_.find(Student(student_code, ""));
}

vector<Student> Dataset::searchStudentsByUcClass(const UcClass& uc_class) const {
    vector<Student> students_in_class;
    for (const Student& student : students_) {
        if (student.isInClass(uc_class)) {
            students_in_class.push_back(student);
        }
    }
    return students_in_class;
}

vector<Student> Dataset::searchStudentsInAtLeastNUCs(int n) const {
    vector<Student> students_in_at_least_n_ucs;
    for (const Student& student : students_) {
        if (student.getUcClasses().size() >= n) {
            students_in_at_least_n_ucs.push_back(student);
        }
    }

    return students_in_at_least_n_ucs;
}

vector<Student> Dataset::searchStudentsInUC(const string& uc_code) const {
    vector<Student> students_in_uc;
    for (const Student& student : students_) {
        for (UcClassConstRef ucClass : student.getUcClasses()) {
            if (ucClass->getUcCode() == uc_code) {
                students_in_uc.push_back(student);
                break;
            }
        }
    }
    return students_in_uc;
}

vector<Student> Dataset::searchStudentsInClass(const string& class_code) const {
    vector<Student> students_in_class;
    for (const Student &student: students_) {
        for (UcClassConstRef ucClass: student.getUcClasses()) {
            if (ucClass->getClassCode() == class_code) {
                students_in_class.push_back(student);
                break;
            }
        }
    }
    return students_in_class;
}

void Dataset::readStudents() {
    const static string STUDENT_CLASSES_PATH = "dataset/students_classes.csv";
    ifstream studentClassesFile(STUDENT_CLASSES_PATH);
    if (studentClassesFile.fail()) {
        ostringstream error_msg;
        error_msg << "Could not open file \"" << STUDENT_CLASSES_PATH << '"';
        throw ios_base::failure(error_msg.str());
    }
    string sstudent_code, student_name, uc_code, class_code, line;
    int student_code;
    getline(studentClassesFile, line);
    Student current_student(-1, "");
    list<UcClass*> classes;
    while (getline(studentClassesFile, sstudent_code, ',')) {
        student_code = stoi(sstudent_code);
        getline(studentClassesFile, student_name, ',');
        getline(studentClassesFile, uc_code, ',');
        getline(studentClassesFile, class_code);
        if (current_student.getStudentCode() != student_code) {
            if (current_student.getStudentCode() != -1)
                students_.insert(current_student);
            current_student = Student(student_code, student_name);
        }
        auto uc_class = findUcClass(uc_code,class_code);
        current_student.getUcClasses().emplace_back(uc_class);
        max_class_capacity_ = max(max_class_capacity_, uc_class->incrementNumberOfStudents());
    }
}

queue<Request>& Dataset::getPendentRequests() {
    return pendent_requests_;
}

const queue<Request>& Dataset::getPendentRequests() const {
    return pendent_requests_;
}

stack<Request>& Dataset::getArchivedRequests() {
    return archived_requests_;
}

const stack<Request>& Dataset::getArchivedRequests() const {
    return archived_requests_;
}

void Dataset::perform(const Request& request) {
    int student_code = request.getStudentCode();
    Student student = *searchStudentByCode(student_code);
    string message;
    switch (request.getType()) {
        case Request::ADD:
            if (canAdd(request, message)) {
                cout << "Student named " << student.getStudentName() << " entered class " <<
                request.getTargetClass()->getUcCode() << '-' << request.getTargetClass()->getClassCode() << endl;

                addUcClass(request, student_code);
            } else {
                cout << "Student named " << student.getStudentName() << " failed to enter class "
                     << request.getTargetClass()->getUcCode() << '-' << request.getTargetClass()->getClassCode() << ": "
                     << message << endl;
            }
            break;
        case Request::REMOVE:
            if (canRemove(request, message)) {
                cout << "Student named " << student.getStudentName() << " left class " <<
                     request.getCurrentClass()->getUcCode() << '-' << request.getCurrentClass()->getClassCode() << endl;

                removeUcClass(request, student_code);
            } else {
                cout << "Student named " << student.getStudentName() << " failed to leave class "
                     << request.getCurrentClass()->getUcCode() << '-' << request.getCurrentClass()->getClassCode() << ": "
                     << message << endl;
            }
            break;
        case Request::SWITCH:
            if (canSwitch(request, message)) {
                cout << "Student named " << student.getStudentName() << " went from class " <<
                     request.getCurrentClass()->getUcCode() << '-' << request.getCurrentClass()->getClassCode() <<
                     " to UcClass " << request.getTargetClass()->getUcCode() << '-'
                     << request.getTargetClass()->getClassCode() << endl;

                removeUcClass(request, student_code);
                addUcClass(request, student_code);
            } else {
                cout << "Student named " << student.getStudentName() << " failed to go from class "
                     << request.getCurrentClass()->getUcCode() << '-' << request.getCurrentClass()->getClassCode()
                     << " to class " << request.getTargetClass()->getUcCode() << '-'
                     << request.getTargetClass()->getClassCode() << ": " << message << endl;
            }
            break;
    }
}

bool Dataset::canAdd(const Request& request, string& message) const {
    const Student& student = *searchStudentByCode(request.getStudentCode());
    for (auto l : request.getTargetClass()->getLessons()) {
        if (student.lessonsOverlapsWith(l)) {
            message = "Has lessons that are not compatible with class "
                + request.getTargetClass()->getClassCode() + " lessons";
            return false;
        }
    }
    if (student.getUcClasses().size() >= 7) {
        message = "Already registered in 7 UCs";
    }
    if (student.isInUc(request.getTargetClass()->getUcCode())) {
        message = "Already in UC " + request.getTargetClass()->getUcCode();
        return false;
    }
    if (isClassFull(*request.getTargetClass())) {
        message = "Class " + request.getTargetClass()->getClassCode() + " is full";
        return false;
    }
    return true;
}

void Dataset::addUcClass(const Request& request, int student_code) {
    UcClassRef uc_class = request.getTargetClass();
    StudentRef student_ref = searchStudentByCode(student_code), old_ref = student_ref;
    Student new_student = *student_ref;
    student_ref++;

    new_student.getUcClasses().insert(new_student.getUcClasses().end(), uc_class);
    students_.erase(old_ref);
    students_.insert(student_ref, new_student);
    uc_class->incrementNumberOfStudents();
}

void Dataset::removeUcClass(const Request& request, int student_code) {
    auto uc_class = request.getCurrentClass();
    StudentRef student_ref = searchStudentByCode(student_code), old_ref = student_ref;
    Student new_student = *student_ref;
    student_ref++;

    new_student.getUcClasses().remove(uc_class);
    students_.erase(old_ref);
    students_.insert(student_ref, new_student);
    uc_class->decrementNumberOfStudents();
}

bool Dataset::canRemove(const Request& request, string& message) const {
    const Student& student = *searchStudentByCode(request.getStudentCode());
    if (student.getUcClasses().size() <= 1) {
        message = "Student must have at least one class";
        return false;
    }
    if (!student.isInClass(*request.getCurrentClass())) {
        message = "Student does not belong to class " + request.getCurrentClass()->getUcCode()
                + '-' + request.getCurrentClass()->getClassCode();
        return false;
    }
    return true;
}

bool Dataset::canSwitch(const Request& request, string& message) const {
    const Student& student = *searchStudentByCode(request.getStudentCode());
    if (student.isInClass(*request.getTargetClass())) {
        message = "Student already in class " + request.getTargetClass()->getUcCode()
                + '-' + request.getTargetClass()->getClassCode();
        return false;
    }
    for (auto l : request.getTargetClass()->getLessons()) {
        if (student.lessonsOverlapsWith(l, *request.getCurrentClass())) {
            message = "Has lessons that are not compatible with class "
                      + request.getTargetClass()->getClassCode() + " lessons";
            return false;
        }
    }
    if (request.getCurrentClass()->getUcCode() != request.getTargetClass()->getUcCode()
        && student.isInUc(request.getTargetClass()->getUcCode())) {
        message = "Already in UC " + request.getTargetClass()->getUcCode();
        return false;
    }
    if (isClassFull(*request.getTargetClass())) {
        message = "Class " + request.getTargetClass()->getUcCode()
                + '-' + request.getTargetClass()->getClassCode() + " is full";
        return false;
    }
    return true;
}

bool Dataset::addBalanceDisturbance(const UcClass& uc_class) const {
    int nmin = uc_class.getNumberOfStudents() + 1, nmax = uc_class.getNumberOfStudents() + 1;
    for (auto other: getClassesInUc(uc_class.getUcCode())) {
        nmin = min(nmin, other->getNumberOfStudents());
        nmax = max(nmax, other->getNumberOfStudents());
    }
    return nmax - nmin > 4;
}

bool Dataset::removeBalanceDisturbance(const UcClass& uc_class) const {
    int nmin = uc_class.getNumberOfStudents() - 1, nmax = uc_class.getNumberOfStudents() - 1;
    for (auto other: getClassesInUc(uc_class.getUcCode())) {
        nmin = min(nmin, other->getNumberOfStudents());
        nmax = max(nmax, other->getNumberOfStudents());
    }
    return nmax - nmin > 4;
}

bool Dataset::switchBalanceDisturbance(const UcClass& from, const UcClass& dest, string& problem_uc_code) const {
    int nmin = dest.getNumberOfStudents() + 1, nmax = dest.getNumberOfStudents() + 1;
    for (auto other: getClassesInUc(dest.getUcCode())) {
        nmin = min(nmin, *other == from ? other->getNumberOfStudents() - 1 : other->getNumberOfStudents());
        nmax = max(nmax, *other == from ? other->getNumberOfStudents() - 1 : other->getNumberOfStudents());
    }
    if (nmax - nmin > 4) {
        problem_uc_code = dest.getUcCode();
        return true;
    }

    nmin = from.getNumberOfStudents() - 1, nmax = from.getNumberOfStudents() - 1;
    for (auto other: getClassesInUc(from.getUcCode())) {
        nmin = min(nmin, *other == dest ? other->getNumberOfStudents() + 1 : other->getNumberOfStudents());
        nmax = max(nmax, *other == dest ? other->getNumberOfStudents() + 1 : other->getNumberOfStudents());
    }
    if (nmax - nmin > 4) {
        problem_uc_code = from.getUcCode();
        return true;
    }
    return false;
}

void Dataset::saveChangesToFile() const {
    const static string STUDENT_CLASSES_PATH = "dataset/students_classes.csv";
    ofstream studentClassesFile(STUDENT_CLASSES_PATH);
    if (studentClassesFile.fail()) {
        ostringstream error_msg;
        error_msg << "Could not open file \"" << STUDENT_CLASSES_PATH << '"';
        throw ios_base::failure(error_msg.str());
    }

    studentClassesFile << "StudentCode,StudentName,UcCode,ClassCode\n";
    for (const Student& student: students_) {
        for (UcClassConstRef uc_class: student.getUcClasses()) {
            studentClassesFile << student.getStudentCode() << ',' << student.getStudentName() << ','
                << uc_class->getUcCode() << ',' << uc_class->getClassCode() << '\n';
        }
    }
}

bool Dataset::isClassFull(const UcClass& uc_class) const {
    return uc_class.getNumberOfStudents() == max_class_capacity_;
}

vector<Lesson> Dataset::getStudentLessons(const Student &student) const {
    vector<Lesson> res, temp;
    for (UcClassConstRef uc_class: student.getUcClasses()) {
        const vector<Lesson>& class_lessons = uc_class->getLessons();
        merge(res.begin(), res.end(), class_lessons.begin(), class_lessons.end(), temp.begin());
        res = temp;
        temp.clear();
    }
    return res;
}

vector<UcClassConstRef> Dataset::getUcClassesByClassCode(const string &class_code) const {
    vector<UcClassConstRef> res;
    for (auto it = uc_classes_.begin(); it != uc_classes_.end(); it++) {
        if (it->getClassCode() == class_code)
            res.push_back(it);
    }
    return res;
}

vector<UcClassRef> Dataset::getUcClassesByClassCode(const string &class_code) {
    vector<UcClassRef> res;
    for (auto it = uc_classes_.begin(); it != uc_classes_.end(); it++) {
        if (it->getClassCode() == class_code)
            res.push_back(it);
    }
    return res;
}

vector<string> Dataset::getUcCodes() const {
    vector<string> res;
    for (const UcClass& uc_class: uc_classes_) {
        if (res.empty() || res.back() != uc_class.getUcCode())
            res.push_back(uc_class.getUcCode());
    }
    return res;
}

vector<UcClassConstRef> Dataset::getClassesByUcCode(const string &uc_code) const {
    vector<UcClassConstRef> res;
    auto it = lower_bound(uc_classes_.begin(), uc_classes_.end(), UcClass(uc_code, ""));
    while (it != uc_classes_.end() && it->getUcCode() == uc_code) {
        res.push_back(it);
        it++;
    }
    return res;
}

std::vector<UcClassRef> Dataset::getClassesByUcCode(const std::string &uc_code) {
    vector<UcClassRef> res;
    auto it = lower_bound(uc_classes_.begin(), uc_classes_.end(), UcClass(uc_code, ""));
    while (it != uc_classes_.end() && it->getUcCode() == uc_code) {
        res.push_back(it);
        it++;
    }
    return res;
}

std::vector<UcClassRef> Dataset::getClassesInUc(const std::string &uc_code) {
    vector<UcClassRef> res;
    auto it = lower_bound(uc_classes_.begin(), uc_classes_.end(), UcClass(uc_code, ""));
    while (it != uc_classes_.end() && it->getUcCode() == uc_code) {
        res.push_back(it);
        it++;
    }
    return res;
}

vector<string> Dataset::getAllClassCodes() const {
    set<string> res;
    for (const UcClass& uc_class: uc_classes_)
        res.insert(uc_class.getClassCode());
    return { res.begin(), res.end() };
}

vector<string> Dataset::getClassCodesByYear(int year) const {
    set<string> res;
    for (const UcClass& uc_class: uc_classes_) {
        if (uc_class.getAcademicYear() == year)
            res.insert(uc_class.getClassCode());
    }
    return { res.begin(), res.end() };
}

vector<UcClassConstRef> Dataset::getClassesInUc(const std::string &uc_code) const {
    vector<UcClassConstRef> res;
    UcClassConstRef it = lower_bound(uc_classes_.begin(), uc_classes_.end(), UcClass(uc_code, ""));
    while (it != uc_classes_.end() && it->getUcCode() == uc_code) {
        res.push_back(it);
        it++;
    }
    return res;
}

vector<Student> Dataset::searchStudentsByAcademicYear(int year) const {
    vector<Student> res;
    for (const Student& student: students_) {
        if (student.getAcademicYear() == year)
            res.push_back(student);
    }
    return res;
}