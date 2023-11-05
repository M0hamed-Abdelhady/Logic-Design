//
// Created by Mohamed Abdelhady on 10/24/2023.
//

#ifndef INC_DF742AC576CB46D89BD963F6F9CFDA90
#define INC_DF742AC576CB46D89BD963F6F9CFDA90

#include "../NumberSystem/binaryInt.h"

namespace BooleanFunctions {

    class TabularMethod {
        char bar;
        std::string separator, secondSeparator;
        int numberOfVariables;
        long long mintermMask, dontCareMask;
        std::vector<int> Minterms, dontCare, index;
        std::vector<std::string> criticalExpression;
        std::map<long long, std::string> unreachable;
        std::map<int, std::map<int, std::vector<std::pair<std::pair<NumberSystem::binaryInt, std::set<int>>, bool>>>> table;
        std::map<std::set<int>, bool> v;

    public:
        TabularMethod();

        TabularMethod(std::vector<int> &minterms, int variables, bool isMinterm = true);

        TabularMethod(std::vector<int> &minterms, std::vector<int> &DontCare, int variables, bool isMinterm = true);

        std::string Simplify();

        void buildTable(std::vector<int> &minterms, int variables);

        void buildTable(std::vector<int> &minterms, std::vector<int> &DontCare, int variables);

    private:

        void combine(int level);

        void determineUnreachableExpressions();

        std::string generateExpression(const std::string &bin);

        long long generateExpressionMask(const std::set<int> &term);

        void determineCriticalExpressions();

        std::string getFullExpression();

        static bool validPair(std::string &a, std::string &b);

        void clearAll();

        int minimizeExpressions(long long takenMask, std::map<long long, std::pair<int, long long>> &dp,
                            std::vector<bool> &vis);
    };

} // BooleanFunctions

#endif //INC_DF742AC576CB46D89BD963F6F9CFDA90
