//
// Created by Mohamed Abdelhady on 10/23/2023.
//

#include "Assistant.h"

char Assistant::bar = '0';

std::string Assistant::separator = " * ", Assistant::secondSeparator = " + ";

std::vector<char> Assistant::VARIABLES{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                       'Q', 'R', 'S',
                                       'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};


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
    for (int i = 1; i <= menu.size(); ++i)
        std::cout << '[' << i << "] " << menu[i - 1] << '\n';
    int lowerLimit = 1, higherLimit = menu.size();
    if (quit)std::cout << "[0] Exit\n", lowerLimit = 0;
    std::cout << "Your Choice:";
    return inputValidChoice(lowerLimit, higherLimit);
}

int Assistant::inputValidChoice(int &lowerLimit, int &higherLimit) {
    std::string choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail() || !isInteger(choice) ||
            std::stoi(choice) > higherLimit || std::stoi(choice) < lowerLimit) {
            std::cout << "ERROR please input a number in range " << lowerLimit << " to " << higherLimit << ":";
            std::cin.ignore();
        } else return stoi(choice);

    }
}

int Assistant::inputValidInteger(bool negative) {
    std::string choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail() || !isInteger(choice) || (std::stoi(choice) < 0 && !negative)) {
            std::cout << "ERROR please input a valid integer:";
            std::cin.ignore();
        } else return stoi(choice);
    }
}

