//
// Created by Mohamed Abdelhady on 11/6/2023.
//

#include "cell.h"

namespace BooleanFunctions {

    cell::cell() : binary(NumberSystem::binaryInt(0)), slots{}, used(false) {}

    cell::cell(NumberSystem::binaryInt &bin, std::set<int> Slots) : used(false) {
        binary = bin, slots = Slots;
    }

    cell::cell(NumberSystem::binaryInt &bin, std::set<int> firstSlots, std::set<int> secondSlots) : used(false) {
        binary = bin;
        slots = Assistant::combineSets(firstSlots, secondSlots);
    }
} // BooleanFunctions