cmake_minimum_required(VERSION 3.8)
project(tic_tac_toe)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Board.cpp Board.h Move.cpp Move.h)
add_executable(tic_tac_toe ${SOURCE_FILES})