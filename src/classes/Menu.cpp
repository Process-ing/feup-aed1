#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

#include "Menu.h"

using namespace std;

Menu::Menu(Dataset& dataset) : dataset_(dataset) {}

void Menu::launch() const {
    const string WELCOME_SCREEN_PATH = "../src/menus/welcome_screen.txt";
    ifstream welcome_screen_file(WELCOME_SCREEN_PATH);
    if (welcome_screen_file.fail()) {
        ostringstream error_msg;
        error_msg << "cannot read menu file \"" << WELCOME_SCREEN_PATH << "\".";
        throw ios_base::failure(error_msg.str());
    }

    cout << welcome_screen_file.rdbuf();

    switch (receiveOption(6)) {
        case 6:
            cout << "Exiting the app. ";
            waitForEnter();
            return;
    }
}

int Menu::receiveOption(int max) {
    int option;
    cout << "Please choose an option: ";
    while (!(cin >> option) || option <= 0 || option > max) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid option. Please choose another option: ";
    }
    return option;
}

void Menu::waitForEnter() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Press ENTER to continue...";
    getchar();
}