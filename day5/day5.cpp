#include "day5.h"

#include <iostream>
#include <fstream>
#include <stack>
#include <deque>
#include <vector>
#include <string>

using std::cin, std::cout, std::endl;
using std::ifstream;
using std::stack;
using std::deque;
using std::vector;
using std::string;

vector<stack<char>> readFile(ifstream& input){
    string currLine;
    vector<deque<char>> vec(10);
    for(int i = 0; i < 8; i++){ //read first 8 lines
        getline(input, currLine);
        int j = 1;
        for(int i = 1; i < currLine.length(); i +=4){
            if(currLine.at(i) != ' '){
                vec.at(j).push_back(currLine.at(i));
            }
            j++;
        }
    }

    vector<stack<char>> stacks(10);
    for(int i = 1; i < 10; i++){
        for(char item : vec.at(i)){
            char tmp = vec.at(i).back();
            vec.at(i).pop_back();
            stacks.at(i).push(tmp);
        }
    }

    return stacks;
}

int day5_part1(){
    cout << "Running Day 5 Part 1..." << endl;
    ifstream inFile("day5/input.txt");
    if(!inFile.is_open()){
        cout << "Could not open file." << endl;
        return -1;
    }

    vector<stack<char>> stacks = readFile(inFile);
    string currLine;

    //Burn next two lines
    getline(inFile, currLine);
    getline(inFile, currLine);
    
    int numToMove, from, to;

    inFile.ignore(5);
    inFile >> numToMove;
    inFile.ignore(6);
    inFile >> from;
    inFile.ignore(4);
    inFile >> to;

    while(!inFile.eof()){
        for(int i = 0; i < numToMove; i++){
            char tmp = stacks.at(from).top();
            stacks.at(from).pop();
            stacks.at(to).push(tmp);
        }
        inFile.ignore(5);
        inFile >> numToMove;
        inFile.ignore(6);
        inFile >> from;
        inFile.ignore(4);
        inFile >> to;
    }

    string tops;
    for(int i = 1; i < 10; i++){
        tops.push_back(stacks.at(i).top());
    }

    cout << "The top of each stack is: " << tops << endl;

    return 0;
}

int day5_part2(){
    cout << "Running Day 5 Part 2..." << endl;
    ifstream inFile("day5/input.txt");
    if(!inFile.is_open()){
        cout << "Could not open file." << endl;
        return -1;
    }

    vector<stack<char>> stacks = readFile(inFile);
    string currLine;

    //Burn next two lines
    getline(inFile, currLine);
    getline(inFile, currLine);
    
    int numToMove, from, to;

    inFile.ignore(5);
    inFile >> numToMove;
    inFile.ignore(6);
    inFile >> from;
    inFile.ignore(4);
    inFile >> to;

    while(!inFile.eof()){
        stack<char> tmpStack;
        for(int i = 0; i < numToMove; i++){
            char tmp = stacks.at(from).top();
            stacks.at(from).pop();
            tmpStack.push(tmp);
        }
        for(int i = 0; i < numToMove; i++){
            stacks.at(to).push(tmpStack.top());
            tmpStack.pop();
        }
        inFile.ignore(5);
        inFile >> numToMove;
        inFile.ignore(6);
        inFile >> from;
        inFile.ignore(4);
        inFile >> to;
    }

    string tops;
    for(int i = 1; i < 10; i++){
        tops.push_back(stacks.at(i).top());
    }

    cout << "The top of each stack is: " << tops << endl;

    return 0;
}

int day5_all(){
    day5_part1();
    day5_part2();
    return 0;
}