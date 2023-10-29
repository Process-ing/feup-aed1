#include <iostream>
#include <fstream>
#include <sstream>

#include "Menu.h"

using namespace std;

Menu::Menu() = default;

void Menu::launch() {
    const string WELCOME_SCREEN_PATH = "../src/menus/welcome_screen.txt";
    ifstream welcome_screen_file(WELCOME_SCREEN_PATH);
    if (welcome_screen_file.fail()) {
        ostringstream error_msg;
        error_msg << "cannot read menu file \"" << WELCOME_SCREEN_PATH << "\".";
        throw ios_base::failure(error_msg.str());
    }

    cout << welcome_screen_file.rdbuf();
}