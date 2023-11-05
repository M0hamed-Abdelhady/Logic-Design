//
// Created by Mohamed Abdelhady on 10/24/2023.
//

#include "TabularMethod.h"

namespace BooleanFunctions {

    TabularMethod::TabularMethod() : bar('0'), separator(" * "), secondSeparator(" + "), numberOfVariables(0),
                                     mintermMask(0), dontCareMask(0), Minterms(), dontCare(), index(),
                                     criticalExpression(), unreachable(), table(), v() {}

    TabularMethod::TabularMethod(std::vector<int> &minterms, int variables, bool isMinterm) {
        numberOfVariables = variables;
        if (isMinterm)separator = " * ", secondSeparator = " + ", bar = '0'; else separator = " + ", secondSeparator = " * ", bar = '1';
        buildTable(minterms, variables);
    }

    TabularMethod::TabularMethod(std::vector<int> &minterms, std::vector<int> &DontCare, int variables,
                                 bool isMinterm) {
        numberOfVariables = variables;
        if (isMinterm)separator = " * ", secondSeparator = " + ", bar = '0'; else separator = " + ", secondSeparator = " * ", bar = '1';
        buildTable(minterms, DontCare, variables);
    }

    std::string TabularMethod::Simplify() {
        this->combine(1);
        this->determineUnreachableExpressions();
        this->determineCriticalExpressions();
        return this->getFullExpression();
    }

    void TabularMethod::buildTable(std::vector<int> &minterms, int variables) {
        clearAll();
        Minterms = minterms, mintermMask = (1 << Minterms.size()) - 1, dontCareMask = 0, numberOfVariables = variables;
        std::sort(Minterms.begin(), Minterms.end());
        int siz = 0;
        for (const auto &i: Minterms) siz = std::max(siz, i);
        index.resize(siz);
        for (int i = 0; i < Minterms.size(); ++i) index[Minterms[i]] = i;
        for (const auto &i: minterms) {
            NumberSystem::binaryInt term(i, numberOfVariables);
            table[1][term.popcount()].emplace_back(make_pair(term, (std::set<int>) {i}), false);
            v[{(int) term.getDecimal()}] = true;
        }
    }

    void
    TabularMethod::buildTable(std::vector<int> &minterms, std::vector<int> &DontCare, int variables) {
        clearAll();
        Minterms = minterms, dontCare = DontCare,
        numberOfVariables = variables;
        for (const auto &i: dontCare) Minterms.push_back(i);
        std::sort(Minterms.begin(), Minterms.end()), mintermMask = (1 << Minterms.size()) - 1;
        int siz = 0;
        for (const auto &i: Minterms) siz = std::max(siz, i);
        index.resize(siz + 1);
        for (int i = 0; i < Minterms.size(); ++i) index[Minterms[i]] = i;
        dontCareMask = generateExpressionMask(std::set<int>(dontCare.begin(), dontCare.end()));
        for (const auto &i: Minterms) {
            NumberSystem::binaryInt term(i, numberOfVariables);
            table[1][term.popcount()].emplace_back(make_pair(term, (std::set<int>) {i}), false);
            v[{(int) term.getDecimal()}] = true;
        }
    }

    void TabularMethod::combine(int level) {
        for (auto group = table[level].begin(); group != table[level].end(); ++group) {
            if (std::next(group) == table[level].end())continue;
            if (abs(std::next(group)->first - group->first) > 1)continue;
            for (auto &i: group->second) {
                for (auto &j: std::next(group)->second) {
                    std::set<int> first = i.first.second;
                    std::string a = i.first.first.getNumber(), b = j.first.first.getNumber();
                    if (validPair(a, b)) {
                        i.second = j.second = true;
                        first.insert(j.first.second.begin(), j.first.second.end());
                        if (!v.count(first))
                            table[level + 1][group->first].emplace_back(make_pair(NumberSystem::binaryInt(a), first),
                                                                        false), v[first] = true;
                    }
                }
            }
        }
        if (table.count(level + 1))combine(level + 1);
    }

    void TabularMethod::determineUnreachableExpressions() {
        for (const auto &level: table) {
            for (const auto &group: level.second) {
                for (const auto &i: group.second) {
                    if (!i.second) {
                        std::string expression = generateExpression(i.first.first.getNumber());
                        if (!expression.empty())
                            unreachable[generateExpressionMask(i.first.second)] = expression;
                    }
                }
            }
        }
    }

    std::string TabularMethod::generateExpression(const std::string &bin) {
        int i = 0;
        std::string expression = "(";
        for (const auto &c: bin) {
            if (c != '_') {
                if (c == bar) {
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

    long long TabularMethod::generateExpressionMask(const std::set<int> &term) {
        long long mask = 0;
        for (const auto &i: term) mask |= 1 << index[i];
        return mask;
    }

    int TabularMethod::minimizeExpressions(long long takenMask, std::map<long long, std::pair<int, long long>> &dp,
                                           std::vector<bool> &vis) {
        if ((!dontCareMask && takenMask == mintermMask) ||
            ((takenMask & ~dontCareMask) == (mintermMask & ~dontCareMask))) {
            return 0;
        }
        if (dp.count(takenMask)) return dp[takenMask].first;
        std::pair<int, long long> ans = {INT_MAX, -1};
        int last = INT_MAX;
        for (const auto &[i, j]: unreachable) {
            if (!vis[i]) {
                vis[i] = true;
                last = 1 + minimizeExpressions(takenMask | i, dp, vis);
                if (last < ans.first) ans = {last, i};
                vis[i] = false;
            }
        }
        dp[takenMask] = ans;
        return ans.first;
    }

    void TabularMethod::determineCriticalExpressions() {
        std::map<long long, std::pair<int, long long>> dp;
        std::vector<bool> vis(mintermMask, false);
        minimizeExpressions(0, dp, vis);
        long long mask = 0;
        while (dp.count(mask)) {
            long long temp = dp[mask].second;
            mask |= temp;
            criticalExpression.emplace_back(unreachable[temp]);
        }
    }

    std::string TabularMethod::getFullExpression() {
        std::string fullExpression;
        std::sort(criticalExpression.begin(), criticalExpression.end());
        for (const auto &term: criticalExpression) {
            fullExpression += term + secondSeparator;
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
        table.clear(), v.clear(), Minterms.clear(), dontCare.clear(), unreachable.clear(), index.clear();
    }

} // BooleanFunctions