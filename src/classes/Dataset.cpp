//
// Created by bruno on 10/20/23.
//

#include "Dataset.h"

using namespace std;

Dataset::Dataset() = default;

const set<Student>& Dataset::getStudents() {
    return students;
}

const set<UcClass>& Dataset::getUcClasses() {
    return ucClasses;
}


