# Version Number
cmake_minimum_required(VERSION 3.0)

# Project Name
project(sim-generator)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../bin)

set(CMAKE_CXX_STANDART 14)
add_definitions(-Wfatal-errors)
add_definitions(-Wall)
add_definitions(-Wextra)
add_definitions(-Weffc++)

include_directories(source)
add_subdirectory(source)


