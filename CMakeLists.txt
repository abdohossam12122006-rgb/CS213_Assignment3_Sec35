cmake_minimum_required(VERSION 4.0)
project(CS213_Assignment3)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(CS213_Assignment3
        src/BoardGame_Classes.h
        src/XO_Classes.cpp
        src/XO_Classes.h
        src/XO_Demo.cpp
        CMakeLists.txt.txt)
