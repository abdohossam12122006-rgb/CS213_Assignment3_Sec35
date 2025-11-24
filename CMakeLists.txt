cmake_minimum_required(VERSION 3.20)
project(CS213_Assignment3)

set(CMAKE_CXX_STANDARD 17)

add_executable(CS213_Assignment3
    main.cpp
    XO_Classes.cpp
    NumericalBoard.cpp
    NumericalUI.cpp
    NumericalPlayer.cpp
 "MisereTicTacToe.h" "DiamondBoard.h" "MisereMinimaxPlayer.h" "MisereUI.h" "DiamondMinimaxPlayer.h" "DiamondUI.h")
target_include_directories(CS213_Assignment3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
