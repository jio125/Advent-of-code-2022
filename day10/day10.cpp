#include "day10.h"

#include <iostream>
#include <fstream>
#include <string>

using std::cin, std::cout, std::endl;
using std::ifstream;
using std::string;

int day10_part1(){
    cout << "Running Day 10 Part 1..." << endl;
    auto start = std::chrono::steady_clock::now();
    ifstream inFile("day10/input.txt");
    if(!inFile.is_open()){
        cout << "Could not read file." << endl;
        return -1;
    }

    string opCode;
    int valToAdd;
    int cycles = 1;
    int xReg = 1;
    bool adding = false; //flag set when executing add
    int sumSigStrength = 0;

    inFile >> opCode; //read first opcode

    while (!inFile.eof()){
        if(((cycles - 20) % 40) == 0){ //If at cycle of interest
            sumSigStrength += cycles * xReg;
        }
        if(adding){ //second cycle of add operation
            adding = false;
            xReg += valToAdd;
            inFile >> opCode;
        }
        else if(opCode == "addx"){ //First cycle of add operation
            adding = true;
            inFile >> valToAdd;
        }
        else if(opCode == "noop"){ //noop instruction
            inFile >> opCode;
        }
        cycles++; //increment cycles
    }
    

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;

    cout << "Sum of signal strengths: " << sumSigStrength << endl;
    cout << "Finished in " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << endl;

    return 0;
}

int day10_part2(){
    cout << "Running Day 10 Part 2..." << endl;
    auto start = std::chrono::steady_clock::now();
    ifstream inFile("day10/input.txt");
    if(!inFile.is_open()){
        cout << "Could not read file." << endl;
        return -1;
    }

    string opCode;
    int valToAdd;
    int cycles = 0;
    int xReg = 1;
    bool adding = false; //flag set when executing add
    bool crt[240] = {false}; // Arrar storing CRT pixels. Screen i 6*40=240

    inFile >> opCode; //read first opcode

    while (!inFile.eof()){
        if(((cycles % 40) == xReg) || ((cycles % 40) == (xReg - 1)) || ((cycles % 40) == (xReg + 1))){ //set CRT pixel to on if the sprite is there
            crt[cycles] = true;
        }
        if(adding){ //second cycle of add operation
            adding = false;
            xReg += valToAdd;
            inFile >> opCode;
        }
        else if(opCode == "addx"){ //First cycle of add operation
            adding = true;
            inFile >> valToAdd;
        }
        else if(opCode == "noop"){ //noop instruction
            inFile >> opCode;
        }
        cycles++; //increment cycles
    }

    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 40; j++){
            if(crt[(i*40)+j]) cout << "#";
            else cout << " ";
        }
        cout << endl;
    }

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;

    cout << "Finished in " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << endl;

    return 0;
}

int day10_all(){
    day10_part1();
    day10_part2();
    return 0;
}