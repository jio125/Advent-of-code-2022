#include "day4.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
using std::vector;
using std::pair;
using std::cout, std::cin, std::endl;
using std::ifstream;

typedef struct elf
{
    int start;
    int end;
} elf;


int day4_part1(){
    cout << "Running Day 4 Puzzle 1..." << endl;
    //open file
    ifstream inFile("day4/input.txt");
    if(!inFile.is_open()){
        cout << "Could not open file." << endl;
        return -1;
    }

    int count = 0;
    elf elf1, elf2;
    char tmp;
    

    inFile >> elf1.start >> tmp;
    inFile >> elf1.end >> tmp;
    inFile >> elf2.start >> tmp;
    inFile >> elf2.end;

    while(!inFile.eof()){
        if((elf1.start <= elf2.start && elf1.end >= elf2.end) || 
            (elf1.start >= elf2.start && elf1.end <= elf2.end)){
            count++;
        }
        inFile >> elf1.start >> tmp;
        inFile >> elf1.end >> tmp;
        inFile >> elf2.start >> tmp;
        inFile >> elf2.end;
    }

    cout << "Puzzle 1 answer: # of ranges fully enclosed = " << count << endl;

    return 0;
}

int day4_part2(){
    cout << "Running Day 4 Puzzle 2..." << endl;
    //open file
    ifstream inFile("day4/input.txt");
    if(!inFile.is_open()){
        cout << "Could not open file." << endl;
        return -1;
    }

    int count = 0;
    elf elf1, elf2;
    char tmp;
    

    inFile >> elf1.start >> tmp;
    inFile >> elf1.end >> tmp;
    inFile >> elf2.start >> tmp;
    inFile >> elf2.end;

    while(!inFile.eof()){
        if((elf1.start <= elf2.start && elf1.end >= elf2.start) || 
            (elf1.start <= elf2.end && elf1.end >= elf2.end) || 
            (elf2.start <= elf1.start && elf2.end >= elf1.start) ||
            (elf2.start <= elf1.end && elf2.end >= elf1.end)){
            count++;
        }
        inFile >> elf1.start >> tmp;
        inFile >> elf1.end >> tmp;
        inFile >> elf2.start >> tmp;
        inFile >> elf2.end;
    }

    cout << "Puzzle 2 answer: # of ranges overlapping = " << count << endl;

    return 0;
}

int day4_all(){
    day4_part1();
    day4_part2();
    return 0;
}