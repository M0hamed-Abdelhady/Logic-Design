//
// Created by Mohamed Abdelhady on 10/23/2023.
//

#include "Assistant.h"

bool Assistant::isInteger(const std::string &s) {
    std::istringstream iss(s);
    int value;
    iss >> value;
    return !iss.fail() && iss.eof();
}

void Assistant::equalizer(std::string &a, std::string &b) {
    if (a.size() < b.size()) a = std::string(b.size() - a.size(), '0') + a;
    else if (a.size() > b.size()) b = std::string(a.size() - b.size(), '0') + b;
}

int Assistant::runMenu(std::vector<std::string> &menu, bool quit) {
    for (int i = 1; i <= menu.size(); ++i) {
        std::cout << '[' << i << "] " << menu[i - 1] << '\n';
    }
    int lowerLimit = 1;
    if (quit)std::cout << "[0] Exit\n", lowerLimit = 0;
    std::cout << "Your Choice:";
    std::string choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail() || !isInteger(choice) || std::stoi(choice) > menu.size() || std::stoi(choice) < 0) {
            std::cout << "ERROR please input a number in range " << lowerLimit << " to " << menu.size() << ":";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else return stoi(choice);

    }
}