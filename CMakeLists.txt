cmake_minimum_required(VERSION 3.11)
project(Advent_of_code_2022)

set(CMAKE_CXX_STANDARD 17)

add_executable(Advent_of_code main.cpp)
target_sources(Advent_of_code PRIVATE day1/day1.cpp day1/day1.h day1/elf.h day1/elf.cpp)
target_sources(Advent_of_code PRIVATE day2/day2.h day2/day2.cpp)
target_sources(Advent_of_code PRIVATE day3/day3.h day3/day3.cpp)