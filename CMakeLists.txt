cmake_minimum_required(VERSION 3.12)
project(AAL)

set(CMAKE_CXX_STANDARD 17)

add_executable(AAL main.cpp Player.cpp Player.h Interface.cpp Interface.h DataGenerator.cpp DataGenerator.h GameTree.cpp GameTree.h)