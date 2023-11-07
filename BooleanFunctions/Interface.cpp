//
// Created by Mohamed Abdelhady on 10/25/2023.
//

#include "Interface.h"

namespace BooleanFunctions {
    void Interface::MainFace() {
        std::cout << "  \t>>> Boolean Functions <<<\n";
        std::vector<std::string> menu{"Simplification Using Tabular Method (aka Quine-McCluskey Method)"};
        while (true) {
            int choice = Assistant::runMenu(menu);
            if (choice == 1)TabularMethodController::start();
            else exit(0);
        }
    }
} // BooleanFunctions