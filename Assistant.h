//
// Created by Mohamed Abdelhady on 10/23/2023.
//

#ifndef INC_95E33D233FE648CB998E7416DDEC8444
#define INC_95E33D233FE648CB998E7416DDEC8444

#include <bits/stdc++.h>

class Assistant {
public:
    inline static char bar = '0';
    inline static std::string separator = " * ", secondSeparator = " + ";
    inline static std::vector<char>
            VARIABLES{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
                      'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};


    static bool isInteger(const std::string &s);

    static int inputValidChoice(int &lowerLimit, int &higherLimit);

    static int inputValidInteger(bool negative = false);

    static void equalizer(std::string &a, std::string &b);

    static int runMenu(std::vector<std::string> &menu, bool quit = true);

    template<typename... Sets>
    inline static std::set<int> combineSets(const Sets &... sets) {
        std::set<int> combinedSet;
        (..., combinedSet.insert(sets.begin(), sets.end()));
        return combinedSet;
    }

};


#endif //INC_95E33D233FE648CB998E7416DDEC8444
