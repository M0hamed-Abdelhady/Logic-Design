//
// Created by Mohamed Abdelhady on 10/25/2023.
//

#ifndef INC_8381416FCD6D4B2A8809DA403377CC2A
#define INC_8381416FCD6D4B2A8809DA403377CC2A

#include "TabularMethod.h"

namespace BooleanFunctions {

    class TabularMethodController {

        static int inputNumberOfVariables();

        static std::vector<int> inputMinterms(bool minterm);

        static std::vector<int> inputDontCare();

        static bool isThereDontCare();

        static bool isMinterm();

        static void printFunction(std::string &expression, const int &variables, bool minterm = true);

    public:
        static void start();
    };

} // BooleanFunctions

#endif //INC_8381416FCD6D4B2A8809DA403377CC2A
