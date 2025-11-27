cmake_minimum_required(VERSION 3.20)
project(CS213_Assignment3)

set(CMAKE_CXX_STANDARD 17)

add_executable(CS213_Assignment3
    main.cpp
    XO_Classes.cpp
    
    
    
 "MisereTicTacToe.h" "DiamondBoard.h" "MisereMinimaxPlayer.h" "MisereUI.h" "DiamondMinimaxPlayer.h" "DiamondUI.h" "SUS_Board.h" "Four_in_a_row_Random_Player" "Four_in_a_row_Random_Player.h"   "NumericalBoard.h" "NumericalUI.h"  "UltimateTicTacToe.h")
target_include_directories(CS213_Assignment3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
