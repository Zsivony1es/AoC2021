cmake_minimum_required(VERSION 3.21)
project(AdventOfCode)

set(CMAKE_CXX_STANDARD 20)

add_executable(AdventOfCode
        inputs/day1.txt
        inputs/day2.txt
        inputs/day3.txt
        inputs/day3_test.txt
        outputs/day1_1
        outputs/day1_2
        outputs/day2_1
        outputs/day3_1
        main.cpp)
