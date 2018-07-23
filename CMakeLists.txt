
cmake_minimum_required(VERSION 3.0)
project(sim-generator)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../bin)

add_executable(
	sim-generator 
	${PROJECT_SOURCE_DIR}/source/main.cpp
	${PROJECT_SOURCE_DIR}/source/communication/BU67103x.cpp
	)



