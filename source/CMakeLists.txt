FILE(GLOB_RECURSE SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
link_directories(externals/aceXtreme/lib/win/x64/release)
add_executable(sim-generator ${SOURCE})

target_link_libraries(sim-generator emacepl)


