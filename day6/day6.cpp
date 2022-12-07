#include "day6.h"

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <list>

using std::list;
using std::unordered_set;
using std::cout, std::cin, std::endl;
using std::ifstream;

bool checkDuplicates(list<char>& list){ //returns true if the given list has a duplicate
    unordered_set<char> s;

    for(auto item : list){
        if(s.find(item) != s.end()){
            return true;
        }
        s.insert(item);
    }
    return false;
}

int day6_part1(){
    cout << "Running Day 6 Puzzle 1..." << endl;
    ifstream inFile("day6/input.txt");
    if(!inFile.is_open()){
        cout << "Could not open file." << endl;
        return -1;
    }

    list<char> charList;
    char currChar;

    //read first 4 chars
    for(int i=0; i < 4; i++){
        inFile >> currChar;
        charList.push_back(currChar);
    }

    int charsRead = 4;

    while (checkDuplicates(charList)){
        inFile >> currChar;
        charList.push_back(currChar);
        charList.pop_front();
        charsRead++;
    }
    


    cout << "Packet starts after character #" << charsRead << "." << endl;    

    return 0;
}

int day6_part2(){
    cout << "Running Day 6 Puzzle 2..." << endl;
    ifstream inFile("day6/input.txt");
    if(!inFile.is_open()){
        cout << "Could not open file." << endl;
        return -1;
    }

    list<char> charList;
    char currChar;

    //read first 14 chars
    for(int i=0; i < 14; i++){
        inFile >> currChar;
        charList.push_back(currChar);
    }

    int charsRead = 14;

    while (checkDuplicates(charList)){
        inFile >> currChar;
        charList.push_back(currChar);
        charList.pop_front();
        charsRead++;
    }
    
    cout << "Message starts after character #" << charsRead << "." << endl;    

    return 0;
}

int day6_all(){
    day6_part1();
    day6_part2();

    return 0;
}