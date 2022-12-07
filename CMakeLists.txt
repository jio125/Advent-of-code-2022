cmake_minimum_required(VERSION 3.11)
project(Advent_of_code_2022)

set(CMAKE_CXX_STANDARD 17)

add_executable(Advent_of_code main.cpp)
target_sources(Advent_of_code PRIVATE day1/day1.cpp day1/day1.h day1/elf.h day1/elf.cpp)
target_sources(Advent_of_code PRIVATE day2/day2.h day2/day2.cpp)
target_sources(Advent_of_code PRIVATE day3/day3.h day3/day3.cpp)
target_sources(Advent_of_code PRIVATE day4/day4.h day4/day4.cpp)
target_sources(Advent_of_code PRIVATE day6/day6.h day6/day6.cpp)
target_sources(Advent_of_code PRIVATE day7/day7.h day7/day7.cpp day7/filesystem.h day7/filesystem.cpp)

add_executable(day7_test day7/main.cpp day7/day7.h day7/day7.cpp day7/filesystem.h day7/filesystem.cpp)
