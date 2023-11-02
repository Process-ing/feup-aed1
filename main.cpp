/**
 * @file main.cpp
 * Main file of project.
 */


#include "Dataset.h"
#include <exception>
#include <iostream>

#include "Menu.h"

using namespace std;

int main() {
    try {
        Dataset dataset;
        Menu menu(dataset);
        menu.launch();
        return 0;
    } catch (const exception& e) {
        cerr << "Error: " << e.what();
        return 1;
    }
}