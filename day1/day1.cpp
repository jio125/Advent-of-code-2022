#include <iostream>
#include <fstream>
#include <vector>
using std::vector;
#include <string>
using std::string;
using std::cout, std::cin, std::endl;

#include "elf.h"
#include "day1.h"

int day1() {
    cout << "Running Day 1 Puzzles 1 and 2..." << endl;
    auto start = std::chrono::steady_clock::now();
    std::ifstream inFile("day1/input.txt");
    if(!inFile.is_open()){
        cout << "Cannot read file" << endl;
        return -1;
    }

    vector<elf*> elves;

    while(!inFile.eof()){
        auto currElf = new elf;
        string currLine;
        std::getline(inFile, currLine);
        while(currLine != "\n"){
            int calories = atoi(currLine.c_str());
            if(calories == 0) break;
            currElf->addItem(calories);
            std::getline(inFile, currLine);
        }
        elves.push_back(currElf);
    }

    int max = 0;
    int second = 0;
    int third = 0;
    for(auto elf : elves){
        int cals = elf->getSum();
        if(cals > max){
            third = second;
            second = max;
            max = cals;
        }
        else if (cals > second){
            third = second;
            second = cals;
        }
        else if (cals > third){
            third = cals;
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;

    cout << "Puzzle 1: The largest number of calories is: " << max << endl;
    cout << "Puzzle 2: Sum of the three largest number of calories is: " << max + second + third << endl;
    cout << "Finished in " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << endl;

    return 0;
}
