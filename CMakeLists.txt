cmake_minimum_required(VERSION 3.2)   # CMake version check
project(unblock-me-solver)               # Create project "simple_example"

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Board.cpp Board.h Block.cpp Block.h globals.h Solver.cpp Solver.h)

add_executable(unblock-me-solver ${SOURCE_FILES})