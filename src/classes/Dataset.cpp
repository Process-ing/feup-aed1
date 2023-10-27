#include "UcClass.h"
#include "Dataset.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <map>
#include <set>
using namespace std;

void Dataset::UcsReader() {
    vector<UcClass> ucClasses;
    set<UcClass> temporary;
    ifstream ucClassFile("../files/classes.csv");
    if (!ucClassFile.is_open()) {
        cout << "Error: Could not open the file " << endl;
        return;
    }
    string line, uc_code, code_of_class;
    getline(ucClassFile, line);
    while (getline(ucClassFile, line)) {
        vector<Lesson> empty;
        istringstream ss(line);
        getline(ss, code_of_class, ',');
        getline(ss, uc_code, ',');
        temporary.insert(UcClass(uc_code, code_of_class, empty));
    }
    for (const UcClass& ucClass : temporary) {
        all_classes.push_back(ucClass);
    }
}



void Dataset::UcClassReader() {
    ifstream ucClassFile("../files/classes.csv");
    if (!ucClassFile.is_open()) {
        cout << "Error: Could not open the file " <<  endl;
        return;
    }
    string line, code_of_class, uc_code, weekday, start, duration, type;
    vector<Lesson> lessons;

    getline(ucClassFile, line);
    while (getline(ucClassFile, line)) {
        stringstream ss(line);
        getline(ss, code_of_class, ',');
        getline(ss, uc_code, ',');
        getline(ss, weekday, ',');
        getline(ss, start, ',');
        getline(ss, duration, ',');
        getline(ss, type, '\r');
        Lesson newLesson(stod(start), stod(duration)+stod(start),type, weekday);
        UcClass temporaryUcClass = findUcClass(uc_code, code_of_class);
        temporaryUcClass.addLesson(newLesson);
    }
}

UcClass Dataset::findUcClass(string uc_code, string code_of_class) {
    UcClass tempUcClass(uc_code, code_of_class, vector<Lesson>());
    for (const UcClass &ucClass: all_classes)
        if (ucClass.getUcCode() == uc_code && ucClass.getCodeOfClass() == code_of_class) {
            return ucClass;
        }

    cout << "This UcClass could not be found." << endl;
    return UcClass();
}
