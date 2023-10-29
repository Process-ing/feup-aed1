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
