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

    static void equalizer(std::string &a, std::string &b);

    static int runMenu(std::vector<std::string> &menu, bool quit = true);

    static std::set<int> combineSets(const std::set<int> &first, const std::set<int> &second);
};


#endif //INC_95E33D233FE648CB998E7416DDEC8444
