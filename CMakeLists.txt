cmake_minimum_required(VERSION 3.10)
project(AdventOfCode VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(SFML_STATIC_LIBRARIES TRUE)

include_directories(src)
# For including headers

add_subdirectory(src)
# Always add executable last!

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} Structures Helpers Solvers)



