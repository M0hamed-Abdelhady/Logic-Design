//
// Created by Mohamed Abdelhady on 10/24/2023.
//

#ifndef INC_DF742AC576CB46D89BD963F6F9CFDA90
#define INC_DF742AC576CB46D89BD963F6F9CFDA90

#include "cell.h"

namespace BooleanFunctions {

    class TabularMethod {
        bool isMinterm;
        int numberOfVariables;
        long long mintermMask, maxtermMask, mintermDontCareMask, maxtermDontCareMask;
        std::string SoPAnswer, PoSAnswer;
        std::vector<int> Minterms, Maxterms, dontCare, mintermIndex, maxtermIndex;
        std::vector<std::string> SoPCriticalExpression, PoSCriticalExpression;
        std::map<long long, std::string> SoPUnreachable, PoSUnreachable;
        std::map<int, std::map<int, std::vector<cell>>> mintermsTable, maxtermsTable;
        std::map<std::set<int>, bool> v;

    public:
        TabularMethod();

        TabularMethod(std::vector<int> &minterms, int variables, bool minterm = true);

        TabularMethod(std::vector<int> &minterms, std::vector<int> &DontCare, int variables, bool minterm = true);

        void Simplify();

        void buildTable(std::vector<int> &minterms, int variables, bool minterm = true);

        void buildTable(std::vector<int> &minterms, std::vector<int> &DontCare, int variables, bool minterm = true);

        bool IsMinterm() const;

        const std::string &SoP() const;

        const std::string &PoS() const;

    private:
        void findTheOtherCanonicalForm();

        void indexing(bool minterm = true);

        void combine(std::map<int, std::map<int, std::vector<cell>>> &table, int level);

        void determineUnreachableExpressions(std::map<int, std::map<int, std::vector<cell>>> &table,
                                             std::map<long long, std::string> &unreachable, bool minterm = true);

        std::string generateExpression(const std::string &bin, bool minterm = true);

        long long generateExpressionMask(const std::set<int> &term, bool minterm = true);

        void determineCriticalExpressions(long long &fullMask, long long &dontCareMask,
                                          std::map<long long, std::string> &unreachable,
                                          std::vector<std::string> &critical);

        std::string
        getFullExpression(std::vector<std::string> &critical, std::string separator = Assistant::secondSeparator);

        static bool validPair(std::string &a, std::string &b);

        void clearAll();

        int minimizeExpressions(long long takenMask, long long &fullMask, long long &dontCareMask,
                                std::map<long long, std::pair<int, long long>> &dp, std::vector<bool> &vis,
                                std::map<long long, std::string> &unreachable);
    };

} // BooleanFunctions

#endif //INC_DF742AC576CB46D89BD963F6F9CFDA90
