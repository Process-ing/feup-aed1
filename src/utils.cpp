#include <algorithm>
#include "utils.h"

using namespace std;

bool compareByName(const Student& studentA, const Student& studentB) {
    return studentA.getStudentName() < studentB.getStudentName();
}

void sortByAlphabeticalOrder(vector<Student>& students) {
    sort(students.begin(), students.end(), compareByName);
}

bool compareByNameReverse(const Student& studentA, const Student& studentB) {
    return studentA.getStudentName() > studentB.getStudentName();
}

void sortByReverseAlphabeticalOrder(vector<Student>& students) {
    sort(students.begin(), students.end(), compareByNameReverse);
}

bool compareByNumUcs(const Student& studentA, const Student& studentB) {
    return studentA.getUcClasses().size() < studentB.getUcClasses().size();
}

void sortByAscendingNumOfUcs(std::vector<Student>& students) {
    sort(students.begin(), students.end(), compareByNumUcs);
}

bool compareByNumUcsReverse(const Student& studentA, const Student& studentB) {
    return studentA.getUcClasses().size() > studentB.getUcClasses().size();
}

void sortByDescendingNumOfUcs(std::vector<Student>& students) {
    sort(students.begin(), students.end(), compareByNumUcsReverse);
}
