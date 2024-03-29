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
    readArchive();
    has_unsaved_changes_ = false;
}

const set<Student>& Dataset::getStudents() const {
    return students_;
}

const vector<UcClass>& Dataset::getUcClasses() const {
    return uc_classes_;
}

int Dataset::getMaxClassCapacity() const {
    return max_class_capacity_;
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
    ifstream student_classes_file(STUDENT_CLASSES_PATH);
    if (student_classes_file.fail()) {
        ostringstream error_msg;
        error_msg << "Could not open file \"" << STUDENT_CLASSES_PATH << '"';
        throw ios_base::failure(error_msg.str());
    }
    string sstudent_code, student_name, uc_code, class_code, line;
    int student_code;
    getline(student_classes_file, line);
    Student current_student(-1, "");
    list<UcClass*> classes;
    while (getline(student_classes_file, sstudent_code, ',')) {
        student_code = stoi(sstudent_code);
        getline(student_classes_file, student_name, ',');
        getline(student_classes_file, uc_code, ',');
        getline(student_classes_file, class_code);
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

void Dataset::readArchive() {
    const static unordered_map<string, Request::Type> STR_TO_TYPE = {
            {"ADD", Request::ADD}, {"REMOVE", Request::REMOVE}, {"SWITCH", Request::SWITCH},
    };
    const static string ARCHIVE_FILEPATH = "dataset/archive.csv";
    ifstream archive_file(ARCHIVE_FILEPATH);
    if (archive_file.fail()) {
        return;
    }

    string type, student_code, curr_uc_code, curr_class_code, target_uc_code, target_class_code, line;
    getline(archive_file, line);
    while (getline(archive_file, type, ',')) {
        getline(archive_file, student_code, ',');
        getline(archive_file, curr_uc_code, ',');
        getline(archive_file, curr_class_code, ',');
        getline(archive_file, target_uc_code, ',');
        getline(archive_file, target_class_code);
        UcClassRef curr_uc_class = findUcClass(curr_uc_code, curr_class_code);
        UcClassRef target_uc_class = findUcClass(target_uc_code, target_class_code);
        request_archive_.emplace_back(STR_TO_TYPE.at(type), stoi(student_code), curr_uc_class, target_uc_class);
    }
}

Request Dataset::popPendentRequest() {
    Request request = pendent_requests_.front();
    pendent_requests_.pop();
    has_unsaved_changes_ = true;
    return request;
}

void Dataset::pushPendentRequest(const Request& request) {
    pendent_requests_.push(request);
    has_unsaved_changes_ = true;
}

const queue<Request>& Dataset::getPendentRequests() const {
    return pendent_requests_;
}

Request Dataset::popArchivedRequest() {
    Request request = request_archive_.back();
    request_archive_.pop_back();
    has_unsaved_changes_ = true;
    return request;
}

void Dataset::pushArchivedRequest(const Request &request) {
    request_archive_.push_back(request);
    has_unsaved_changes_ = true;
}

const deque<Request>& Dataset::getArchivedRequests() const {
    return request_archive_;
}

bool Dataset::canAdd(const Request& request, string& message) const {
    const Student& student = *searchStudentByCode(request.getStudentCode());
    for (auto l : request.getTargetClass()->getLessons()) {
        if (student.lessonsIncompatibleWith(l)) {
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

void Dataset::addUcClass(UcClassRef uc_class, int student_code) {
    StudentRef student_ref = searchStudentByCode(student_code), old_ref = student_ref;
    Student new_student = *student_ref;
    student_ref++;

    new_student.getUcClasses().insert(new_student.getUcClasses().end(), uc_class);
    students_.erase(old_ref);
    students_.insert(student_ref, new_student);
    uc_class->incrementNumberOfStudents();
    has_unsaved_changes_ = true;
}

void Dataset::removeUcClass(UcClassRef uc_class, int student_code) {
    StudentRef student_ref = searchStudentByCode(student_code), old_ref = student_ref;
    Student new_student = *student_ref;
    student_ref++;

    new_student.getUcClasses().remove(uc_class);
    students_.erase(old_ref);
    students_.insert(student_ref, new_student);
    uc_class->decrementNumberOfStudents();
    has_unsaved_changes_ = true;
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
        if (student.lessonsIncompatibleWith(l, *request.getCurrentClass())) {
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

void Dataset::saveChangesToFile() {
    const static string STUDENT_CLASSES_FILEPATH = "dataset/students_classes.csv";
    ofstream student_classes_file(STUDENT_CLASSES_FILEPATH);
    if (student_classes_file.fail()) {
        ostringstream error_msg;
        error_msg << "Could not open file \"" << STUDENT_CLASSES_FILEPATH << '"';
        throw ios_base::failure(error_msg.str());
    }

    student_classes_file << "StudentCode,StudentName,UcCode,ClassCode\n";
    for (const Student& student: students_) {
        for (UcClassConstRef uc_class: student.getUcClasses()) {
            student_classes_file << student.getStudentCode() << ',' << student.getStudentName() << ','
                << uc_class->getUcCode() << ',' << uc_class->getClassCode() << '\n';
        }
    }

    const static unordered_map<Request::Type, string> TYPE_TO_STR = {
        {Request::ADD, "ADD"}, {Request::REMOVE, "REMOVE"}, {Request::SWITCH, "SWITCH"},
    };
    const static string ARCHIVE_FILEPATH = "dataset/archive.csv";
    ofstream archive_file(ARCHIVE_FILEPATH);

    archive_file << "Type,StudentCode,CurrentUcCode,CurrentClassCode,TargetUcCode,TargetClassCode\n";
    for (const Request& request: request_archive_) {
        archive_file << TYPE_TO_STR.at(request.getType()) << ',' << request.getStudentCode() << ','
            << request.getCurrentClass()->getUcCode() << ',' << request.getCurrentClass()->getClassCode() << ','
            << request.getTargetClass()->getUcCode() << ',' << request.getTargetClass()->getClassCode() << '\n';
    }
    has_unsaved_changes_ = false;
}

bool Dataset::hasUnsavedChanges() const {
    return has_unsaved_changes_;
}

bool Dataset::isClassFull(const UcClass& uc_class) const {
    return uc_class.getNumberOfStudents() == max_class_capacity_;
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