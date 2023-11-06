//
// Created by Mohamed Abdelhady on 11/6/2023.
//

#ifndef INC_A73233655D494E9E9270EE7FD5806AE4
#define INC_A73233655D494E9E9270EE7FD5806AE4

#include "../NumberSystem/binaryInt.h"

namespace BooleanFunctions {
    class cell {
    public:
        NumberSystem::binaryInt binary;
        std::set<int> slots;
        bool used;

    public:
        cell();

        cell(NumberSystem::binaryInt &bin, std::set<int> Slots);

        cell(NumberSystem::binaryInt &bin, std::set<int> firstSlots, std::set<int> secondSlots);
    };

} // BooleanFunctions

#endif //INC_A73233655D494E9E9270EE7FD5806AE4
