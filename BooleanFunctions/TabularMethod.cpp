//
// Created by Mohamed Abdelhady on 10/24/2023.
//

#include "TabularMethod.h"

namespace BooleanFunctions {

    TabularMethod::TabularMethod() : isMinterm(true), numberOfVariables(0), mintermMask(0), mintermDontCareMask(0),
                                     Minterms(),
                                     dontCare(), mintermIndex(), SoPCriticalExpression(), SoPUnreachable(),
                                     mintermsTable(),
                                     v() {}

    TabularMethod::TabularMethod(std::vector<int> &minterms, int variables, bool minterm) {
        buildTable(minterms, variables, minterm);
    }

    TabularMethod::TabularMethod(std::vector<int> &minterms, std::vector<int> &DontCare, int variables, bool minterm) {
        buildTable(minterms, DontCare, variables, minterm);
    }

    void TabularMethod::Simplify() {
///     Simplify in SoP Form
        this->combine(mintermsTable, 1);
        this->determineUnreachableExpressions(mintermsTable, SoPUnreachable);
        this->determineCriticalExpressions(mintermMask, mintermDontCareMask, SoPUnreachable, SoPCriticalExpression);
        this->SoPAnswer = this->getFullExpression(SoPCriticalExpression);
        v.clear();
///     Simplify in PoS Form
        this->combine(maxtermsTable, 1);
        this->determineUnreachableExpressions(maxtermsTable, PoSUnreachable, false);
        this->determineCriticalExpressions(maxtermMask, maxtermDontCareMask, PoSUnreachable, PoSCriticalExpression);
        this->PoSAnswer = this->getFullExpression(PoSCriticalExpression, Assistant::separator);
    }

    void TabularMethod::buildTable(std::vector<int> &minterms, int variables, bool minterm) {
        clearAll();
        Minterms = minterms, numberOfVariables = variables, mintermDontCareMask = 0;
        isMinterm = minterm;
        indexing(isMinterm);
        findTheOtherCanonicalForm();
        indexing(!isMinterm);
        mintermMask = (1 << Minterms.size()) - 1, maxtermMask = (1 << Maxterms.size()) - 1;
///     Building Minterms Table
        for (const auto &i: Minterms) {
            NumberSystem::binaryInt term(i, numberOfVariables);;
            mintermsTable[1][term.popcount()].emplace_back(cell(term, {i}));
            v[{i}] = true;
        }
///     Building Maxterms Table
        for (const auto &i: Maxterms) {
            NumberSystem::binaryInt term(i, numberOfVariables);
            maxtermsTable[1][term.popcount()].emplace_back(cell(term, {i}));
            v[{i}] = true;
        }
    }

    void
    TabularMethod::buildTable(std::vector<int> &minterms, std::vector<int> &DontCare, int variables, bool minterm) {
        clearAll();
        Minterms = minterms, dontCare = DontCare, numberOfVariables = variables;
        isMinterm = minterm;
        indexing(isMinterm);
        findTheOtherCanonicalForm();
        indexing(!isMinterm);
        mintermMask = (1 << Minterms.size()) - 1, maxtermMask = (1 << Maxterms.size()) - 1;
        mintermDontCareMask = generateExpressionMask(std::set<int>(dontCare.begin(), dontCare.end()));
        maxtermDontCareMask = generateExpressionMask(std::set<int>(dontCare.begin(), dontCare.end()), false);
///     Building Minterms Table
        for (const auto &i: Minterms) {
            NumberSystem::binaryInt term(i, numberOfVariables);
            mintermsTable[1][term.popcount()].emplace_back(cell(term, {i}));
            v[{i}] = true;
        }
///     Building Maxterms Table
        for (const auto &i: Maxterms) {
            NumberSystem::binaryInt term(i, numberOfVariables);
            maxtermsTable[1][term.popcount()].emplace_back(cell(term, {i}));
            v[{i}] = true;
        }
    }

    void TabularMethod::findTheOtherCanonicalForm() {
        if (isMinterm) {
///         Find Maxterms
            for (int i = 0; i < 1 << numberOfVariables; ++i)
                if (!~mintermIndex[i])Maxterms.push_back(i);
        } else {
///         Find Minterms
            for (int i = 0; i < 1 << numberOfVariables; ++i)
                if (!~maxtermIndex[i])Minterms.push_back(i);
        }
    }

    void TabularMethod::indexing(bool minterm) {
        if (minterm) {
///         Adding don't care to Minterms
            if (!dontCare.empty())
                for (const auto &i: dontCare) Minterms.push_back(i);
///         Minterms indexing
            std::sort(Minterms.begin(), Minterms.end());
            mintermIndex.resize(*std::max_element(Minterms.begin(), Minterms.end()) + 1, -1);
            for (int i = 0; i < Minterms.size(); ++i) mintermIndex[Minterms[i]] = i;
        } else {
///         Adding don't care to Maxterms
            if (!dontCare.empty())
                for (const auto &i: dontCare) Maxterms.push_back(i);
///         Maxterms indexing
            std::sort(Maxterms.begin(), Maxterms.end());
            maxtermIndex.resize(*std::max_element(Maxterms.begin(), Maxterms.end()) + 1, -1);
            for (int i = 0; i < Maxterms.size(); ++i) maxtermIndex[Maxterms[i]] = i;
        }
    }

    void TabularMethod::combine(std::map<int, std::map<int, std::vector<cell>>> &table, int level) {
        for (auto group = table[level].begin(); group != table[level].end(); ++group) {
            if (std::next(group) == table[level].end())continue;
            if (abs(std::next(group)->first - group->first) > 1)continue;
            for (auto &i: group->second) {
                for (auto &j: std::next(group)->second) {
                    std::string a = i.binary.getNumber(), b = j.binary.getNumber();
                    if (validPair(a, b)) {
                        i.used = j.used = true;
                        std::set<int> combined = Assistant::combineSets(i.slots, j.slots);
                        NumberSystem::binaryInt x = i.binary;
                        x.setValue(a);
                        if (!v.count(combined))
                            table[level + 1][group->first].emplace_back(x, combined), v[combined] = true;
                    }
                }
            }
        }
        if (mintermsTable.count(level + 1))combine(table, level + 1);
    }

    void TabularMethod::determineUnreachableExpressions(std::map<int, std::map<int, std::vector<cell>>> &table,
                                                        std::map<long long, std::string> &unreachable, bool minterm) {
        for (const auto &level: table) {
            for (const auto &group: level.second) {
                for (const auto &i: group.second) {
                    if (!i.used) {
                        std::string expression = generateExpression(i.binary.getNumber(), minterm);
                        if (!expression.empty())
                            unreachable[generateExpressionMask(i.slots, minterm)] = expression;
                    }
                }
            }
        }
    }

    std::string TabularMethod::generateExpression(const std::string &bin, bool minterm) {
        int i = 0;
        std::string expression = "(", separator = (minterm ? Assistant::separator : Assistant::secondSeparator);
        for (const auto &c: bin) {
            if (c != '_') {
                if ((c == Assistant::bar && minterm) || (c != Assistant::bar && !minterm)) {
                    expression.push_back(Assistant::VARIABLES[i]);
                    expression.push_back('\'');
                    expression += separator;
                } else {
                    expression.push_back(Assistant::VARIABLES[i]);
                    expression += separator;
                }
            }
            ++i;
        }
        expression.pop_back(), expression.pop_back(), expression.back() = ')';
        return expression;
    }

    long long TabularMethod::generateExpressionMask(const std::set<int> &term, bool minterm) {
        long long mask = 0;
        for (const auto &i: term) mask |= 1 << (minterm ? mintermIndex[i] : maxtermIndex[i]);
        return mask;
    }

    int TabularMethod::minimizeExpressions(long long takenMask, long long &fullMask, long long &dontCareMask,
                                           std::map<long long, std::pair<int, long long>> &dp, std::vector<bool> &vis,
                                           std::map<long long, std::string> &unreachable) {
        if ((!dontCareMask && takenMask == fullMask) ||
            ((takenMask & ~dontCareMask) == (fullMask & ~dontCareMask))) {
            return 0;
        }
        if (dp.count(takenMask)) return dp[takenMask].first;
        std::pair<int, long long> ans = {INT_MAX, -1};
        int last = INT_MAX;
        for (const auto &[i, j]: unreachable) {
            if (!vis[i]) {
                vis[i] = true;
                last = 1 + minimizeExpressions(takenMask | i, fullMask, dontCareMask, dp, vis, unreachable);
                if (last < ans.first) ans = {last, i};
                vis[i] = false;
            }
        }
        dp[takenMask] = ans;
        return ans.first;
    }

    void TabularMethod::determineCriticalExpressions(long long &fullMask, long long &dontCareMask,
                                                     std::map<long long, std::string> &unreachable,
                                                     std::vector<std::string> &critical) {
        std::map<long long, std::pair<int, long long>> dp;
        std::vector<bool> vis(fullMask, false);
        minimizeExpressions(0, fullMask, dontCareMask, dp, vis, unreachable);
        long long mask = 0;
        while (dp.count(mask)) {
            long long temp = dp[mask].second;
            mask |= temp;
            critical.emplace_back(unreachable[temp]);
        }
    }

    std::string TabularMethod::getFullExpression(std::vector<std::string> &critical, std::string separator) {
        std::string fullExpression;
        std::sort(critical.begin(), critical.end());
        for (const auto &term: critical) {
            fullExpression += term + separator;
        }
        fullExpression.pop_back(), fullExpression.pop_back(), fullExpression.pop_back();
        return fullExpression;
    }

    bool TabularMethod::validPair(std::string &a, std::string &b) {
        int diff = 0, index = 0;
        Assistant::equalizer(a, b);
        for (int i = 0; i < a.size(); ++i) {
            if ((a[i] == '_' && b[i] != '_') || (a[i] != '_' && b[i] == '_'))return false;
            if (a[i] != b[i])
                ++diff, index = i;
            if (diff > 1)return false;
        }
        a[index] = b[index] = '_';
        return true;
    }

    void TabularMethod::clearAll() {
        mintermsTable.clear(), maxtermsTable.clear(), v.clear(),
                Minterms.clear(), Maxterms.clear(), dontCare.clear(),
                SoPUnreachable.clear(), mintermIndex.clear(), maxtermIndex.clear();
    }

    bool TabularMethod::IsMinterm() const {
        return isMinterm;
    }

    const std::string &TabularMethod::SoP() const {
        return SoPAnswer;
    }

    const std::string &TabularMethod::PoS() const {
        return PoSAnswer;
    }

} // BooleanFunctions