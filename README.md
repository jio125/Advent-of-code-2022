# Advent of code 2022

![Current Day Badge](https://img.shields.io/badge/day%20📅-8-blue)
![Stars Badge](https://img.shields.io/badge/stars%20⭐-16-yellow)
![Days Completed Badge](https://img.shields.io/badge/days%20completed-8-red)

Repository for [Advent of Code 2022](https://adventofcode.com/)

See [wiki](https://github.com/jio125/Advent-of-code-2022/wiki) for each day's puzzles and implementation notes.

See subfolders for each day's solutions.

Everything is written in C++

We'll see how far I get...

## Usage

CMake version 3.11 or higher required.

All commands executed from root directory.

Generate Project Buildsystem:

`cmake -B build`

Compile:

`cmake --build build`

Run:

`./build/Advent_of_code <Day> <Puzzle>`

`./build/Advent_of_code -h` for help.

- See each day's subfolder for instructions on how to run specific puzzles

## Timing

Each days puzzles are timed using the `<chrono>` library.

- Timing starts after `Running Day X Part X...` is printed to the terminal but before the input file is opened.
- Timing stops after the calculation is completed but before the solution is printed to the terminal.
- The time to execute is printed after the solution in milliseconds.
