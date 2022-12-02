#include <iostream>
#include <fstream>
#include <vector>
using std::vector;
#include <string>
using std::string;
using std::cout, std::cin, std::endl;

#include "elf.h"

int main() {
    std::ifstream inFile("input.txt");
    if(inFile.bad()){
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

    cout << "The largest number of calories is: " << max << endl;
    cout << "Sum of the three largest number of calories is: " << max + second + third << endl;

    return 0;
}
