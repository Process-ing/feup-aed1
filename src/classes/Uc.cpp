#include "Uc.h"
#include <string>
using namespace std;

Uc::Uc(string ucCode, string codeOfClass){
    this->ucCode_ = ucCode;
    this->codeOfClass_ = codeOfClass;
    this->numberOfStudents_ = 0;
    this->maxCapacity_ = 0;
}

string Uc::get_ucCode() const {
    return ucCode_;
}

string Uc::get_codeOfClass() const {
    return codeOfClass_;
}

int Uc::get_numberOfStudents() const {
    return numberOfStudents_;
}

int Uc::get_maxCapacity() const {
    return maxCapacity_;

void Uc::set_maxCapacity(int newMaxCapacity){
    numberOfStudents_ = newMaxCapacity;
}

void Uc::set_maxCapacity(int newMaxCapacity){
    maxCapacity_ = newMaxCapacity;
}
}