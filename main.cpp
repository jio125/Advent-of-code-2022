#include <iostream>
#include <string>
#include <cstring>
#include "advent_of_code.h"

using std::cout, std::cin, std::endl;

int main(int argc, char **argv) {
    cout << "Welcome to the Advent of Code 2022 project!" << endl;

    if(strcmp(argv[1], "-h") == 0){
        cout << "Advent_of_code <Day> <Puzzle>" << endl;
        cout << "-h Help" << endl;
        cout << "See github repo for more details." << endl;
        return 0;
    }

    if(argc < 3){
        cout << "Please specify both a day and puzzle to run. run Advent_of_code -h for help." << endl;
        return 0;
    }

    //parse CLI parameters as integers
    int arg1 = atoi(argv[1]);
    int arg2 = atoi(argv[2]);

    switch (arg1)
    {
    case 1:
        DAY1; //Day 1 puzzles are implemented together
        break;
    case 2:
        switch(arg2){ //
            case 0:
                DAY2_ALL;
                break;
            case 1:
                DAY2_PART1;
                break;
            case 2:
                DAY2_PART2;
                break;
            default:
                cout << "Invalid puzzle input \"" << arg2 << "\". Please choose between 0-2." << endl;
                break;
        }
        break;
    case 3:
        switch(arg2){
            case 0:
                DAY3_ALL;
                break;
            case 1:
                DAY3_PART1;
                break;
            case 2:
                DAY3_PART2;
                break;
            case 3:
                DAY3_PART2_NEW;
                break;
            default:
                cout << "Invalid puzzle input \"" << arg2 << "\". Please choose between 0-3." << endl;
                break;
        }
        break;
    case 4:
        switch(arg2){ //
                case 0:
                    DAY4_ALL;
                    break;
                case 1:
                    DAY4_PART1;
                    break;
                case 2:
                    DAY4_PART2;
                    break;
                default:
                    cout << "Invalid puzzle input \"" << arg2 << "\". Please choose between 0-2." << endl;
                    break;
            }
            break;
    case 5:
        switch(arg2){ //
                case 0:
                    DAY5_ALL;
                    break;
                case 1:
                    DAY5_PART1;
                    break;
                case 2:
                    DAY5_PART2;
                    break;
                default:
                    cout << "Invalid puzzle input \"" << arg2 << "\". Please choose between 0-2." << endl;
                    break;
            }
            break;
    case 6:
        switch(arg2){ //
                case 0:
                    DAY6_ALL;
                    break;
                case 1:
                    DAY6_PART1;
                    break;
                case 2:
                    DAY6_PART2;
                    break;
                default:
                    cout << "Invalid puzzle input \"" << arg2 << "\". Please choose between 0-2." << endl;
                    break;
            }
            break;
    case 7:
        switch(arg2){ //
                case 0:
                    DAY7_ALL;
                    break;
                case 1:
                    DAY7_PART1;
                    break;
                case 2:
                    DAY7_PART2;
                    break;
                default:
                    cout << "Invalid puzzle input \"" << arg2 << "\". Please choose between 0-2." << endl;
                    break;
            }
            break;
    case 8:
        switch(arg2){ //
                case 0:
                    DAY8_ALL;
                    break;
                case 1:
                    DAY8_PART1;
                    break;
                case 2:
                    DAY8_PART2;
                    break;
                default:
                    cout << "Invalid puzzle input \"" << arg2 << "\". Please choose between 0-2." << endl;
                    break;
            }
            break;
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
        cout << "This day's puzzles have not been implemented yet." << endl;
        break;
    default:
        cout << "Invalid day \"" << arg1 << "\"." << endl;
        break;
    }

    return 0;
}
