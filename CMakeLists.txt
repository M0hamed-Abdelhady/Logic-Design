cmake_minimum_required(VERSION 3.26)
project(Logic_Design)

set(CMAKE_CXX_STANDARD 17)

add_executable(Logic_Design main.cpp
        BooleanFunctions/TabularMethod.cpp
        NumberSystem/binaryInt.cpp
        Assistant.cpp
        BooleanFunctions/Interface.cpp
        BooleanFunctions/TabularMethodController.cpp)
