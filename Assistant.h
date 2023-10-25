//
// Created by Mohamed Abdelhady on 10/23/2023.
//

#ifndef INC_95E33D233FE648CB998E7416DDEC8444
#define INC_95E33D233FE648CB998E7416DDEC8444

#include <bits/stdc++.h>

class Assistant {
public:
    inline static std::vector<char>
            VARIABLES{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
                      'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};


    static bool isInteger(const std::string &s);

    static void equalizer(std::string &a, std::string &b);

    static int runMenu(std::vector<std::string> &menu, bool quit = true);
};


#endif //INC_95E33D233FE648CB998E7416DDEC8444
