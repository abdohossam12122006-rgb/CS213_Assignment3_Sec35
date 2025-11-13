cmake_minimum_required(VERSION 3.10)
project(BoardGameFramework)

set(CMAKE_CXX_STANDARD 17)
include_directories(${PROJECT_SOURCE_DIR})

add_executable(XO_Demo 
    XO_Demo.cpp 
    NumericalBoard.cpp
    NumericalUI.cpp
    NumericalPlayer.cpp
)