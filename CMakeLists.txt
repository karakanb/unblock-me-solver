cmake_minimum_required(VERSION 3.2)
project(unlock-me-solver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Board.cpp Board.h Block.cpp Block.h globals.h Solver.cpp Solver.h globals.h)
add_executable(unlock-me-solver ${SOURCE_FILES})