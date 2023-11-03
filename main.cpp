/**
 * @file main.cpp
 * Main file of project.
 */


#include "Dataset.h"
#include <exception>
#include <iostream>

#include "Window.h"

using namespace std;

int main() {
    try {
        Dataset dataset;
        Window menu(dataset);
        menu.launch();
        return 0;
    } catch (const exception& e) {
        cerr << "Error: " << e.what();
        return 1;
    }
}