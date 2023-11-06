//
// Created by Mohamed Abdelhady on 10/25/2023.
//

#include "TabularMethodController.h"

namespace BooleanFunctions {

    void TabularMethodController::start() {
        int numberOfVariables = inputNumberOfVariables();
        bool Minterm = isMinterm();
        std::vector<int> minterms = inputMinterms(Minterm);
        std::string simplifiedFunction;
        if (isThereDontCare()) {
            std::vector<int> dontCare = inputDontCare();
            TabularMethod fx(minterms, dontCare, numberOfVariables, Minterm);
            fx.Simplify();
            printFunction(const_cast<std::string &>(fx.SoP()), numberOfVariables);
            printFunction(const_cast<std::string &>(fx.PoS()), numberOfVariables, false);
        } else {
            TabularMethod fx(minterms, numberOfVariables, Minterm);
            fx.Simplify();
            printFunction(const_cast<std::string &>(fx.SoP()), numberOfVariables);
            printFunction(const_cast<std::string &>(fx.PoS()), numberOfVariables, false);
        }
        std::cout << '\n';
    }

    int TabularMethodController::inputNumberOfVariables() {
        int numberOfVariables;
        std::cout << "Number of Variables:";
        std::cin >> numberOfVariables;
        return numberOfVariables;
    }

    std::vector<int> TabularMethodController::inputMinterms(bool minterm) {
        int numberOfMinterms;
        std::string type = minterm ? "Minterms" : "Maxterm";
        std::cout << "Number of " << type << ':';
        std::cin >> numberOfMinterms;
        std::vector<int> minterms(numberOfMinterms);
        std::cout << "Input " << type << "\n>>";
        for (int i = 0; i < numberOfMinterms; ++i) std::cin >> minterms[i];
        return minterms;
    }

    std::vector<int> TabularMethodController::inputDontCare() {
        int numberOfDontCare;
        std::cout << "Number of don't care input:";
        std::cin >> numberOfDontCare;
        std::vector<int> dontCare(numberOfDontCare);
        std::cout << "Input the don't care input\n>>";
        for (int i = 0; i < numberOfDontCare; ++i) std::cin >> dontCare[i];
        return dontCare;
    }

    bool TabularMethodController::isThereDontCare() {
        std::cout << "Is there a Don't-Care Input?\n";
        std::vector<std::string> menu{"Yes", "No"};
        return Assistant::runMenu(menu, false) == 1;
    }

    bool TabularMethodController::isMinterm() {
        std::cout << "  Choose Input Type (you will get both `PoS` and `SoP` Forms)\n";
        std::vector<std::string> menu{"Minterm", "Maxterm"};
        return Assistant::runMenu(menu, false) == 1;
    }

    void TabularMethodController::printFunction(std::string &expression, const int &variables, bool minterm) {
        std::cout << '\n';
        std::cout << (minterm ? "<SoP Form> " : "<PoS Form> ");
        std::cout << "->  F(";
        for (int i = 0; i < variables; ++i) {
            std::cout << Assistant::VARIABLES[i];
            if (i != variables - 1)std::cout << ", ";
        }
        std::cout << ") = ";
        std::cout << expression << '\n';
    }
} // BooleanFunctions