cmake_minimum_required(VERSION 3.6)
project(HashTable)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES HashTable.h GameOfLifeMap.cpp)
add_executable(HashTable ${SOURCE_FILES})