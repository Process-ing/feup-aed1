/**
 * Main file of project.
 */

#include <exception>
#include <iostream>

#include "Menu.h"

using namespace std;

int main() {
    Menu menu;

    try {
        menu.launch();
        return 0;
    } catch (const exception& e) {
        cerr << "Error: " << e.what();
        return 1;
    }
}