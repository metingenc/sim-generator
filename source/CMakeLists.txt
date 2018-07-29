FILE(GLOB_RECURSE SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(sim-generator ${SOURCE})

target_link_libraries(sim-generator emacepl)



