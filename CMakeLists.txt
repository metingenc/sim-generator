# Version Number
cmake_minimum_required(VERSION 3.0)

# Cmake Build Type
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")


# Project Name
project(sim-generator)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDART 14)
add_definitions(-Wfatal-errors)
add_definitions(-Wall)
add_definitions(-Wextra)
add_definitions(-Weffc++)

include_directories(source)
include_directories(externals/aceXtreme/include)
link_directories(externals/aceXtreme/lib/win/x64/release)

add_subdirectory(source)


