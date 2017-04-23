cmake_minimum_required(VERSION 3.2)
project(unblock-me-solver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/Board.cpp src/Board.h src/Block.cpp src/Block.h src/globals.h src/Solver.cpp src/Solver.h)

add_executable(unblock-me-solver.out ${SOURCE_FILES})