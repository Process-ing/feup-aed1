//
// Created by bruno on 10/20/23.
//

#include "Dataset.h"

using namespace std;

Dataset::Dataset() = default;

const set<Student>& Dataset::getStudents() const {
    return students_;
}

const set<UcClass>& Dataset::getUcClasses() const {
    return uc_classes_;
}
