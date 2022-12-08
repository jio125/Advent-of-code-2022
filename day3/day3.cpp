//
// Created by Jiovanni Ortiz-Anglero on 12/3/22.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <set>
#include <chrono>

using std::set;
using std::vector;
using std::string;
using std::cout, std::cin, std::endl;
using std::ifstream;

#include "day3.h"

int day3_all(){
    
    day3_part1();
    day3_part2();
    day3_part2_newMethod();

    return 0;
}

int day3_part1(){
    cout << "Running Day 3 Part 1..." << endl;
    auto start = std::chrono::steady_clock::now();
    //open file
    ifstream inFile("day3/input.txt");
    if(!inFile.is_open()){
        cout << "Could not open file" << endl;
        return -1;
    }

    vector<string> sacks;
    string currSack;

    inFile >> currSack;
    while(!inFile.eof()){
        sacks.push_back(currSack);
        inFile >> currSack;
    }

    int totalPriority = 0;
    for(const auto& sack : sacks){
        int subLen = sack.length()/2;
        for(int i = 0; i < subLen; i++){
            size_t found = sack.find(sack.at(i), subLen);
            if(found != string::npos){
                char item = sack.at(i);
                if(item >= 'a'){
                    item -= 96;
                    totalPriority += item;
                }
                else if(item >= 'A'){
                    item = item - 64 + 26;
                    totalPriority += item;
                }
                break;
            }
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;

    cout << "Total priority for part 1 is: " << totalPriority << endl;
    cout << "Finished in " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << endl;

    inFile.close();

    return 0;
}

int day3_part2(){
    cout << "Running Day 3 Part 2..." << endl;
    auto start = std::chrono::steady_clock::now();
    //open file
    ifstream inFile("day3/input.txt");
    if(!inFile.is_open()){
        cout << "Could not open file" << endl;
        return -1;
    }

    vector<string> sacks;
    string currSack;

    inFile >> currSack;
    while(!inFile.eof()){
        sacks.push_back(currSack);
        inFile >> currSack;
    }

    inFile.close();

    int totalPriority = 0;

    for(unsigned long i = 0; i < sacks.size(); i +=3){
        set<char> s1;
        set<char> s2;
        for(char item : sacks.at(i)){
            s1.insert(item);
        }
        for (char item : sacks.at(i+1)) {
            s2.insert(item);
        }
        for (char item : sacks.at(i+2)){
            if(s1.find(item) != s1.end() && s2.find(item) != s2.end()){
                if(item >= 'a'){
                    item -= 96;
                    totalPriority += item;
                }
                else if(item >= 'A'){
                    item = item - 64 + 26;
                    totalPriority += item;
                }
                break;
            }
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;

    cout << "Total priority for part 2 is: " << totalPriority << endl;
    cout << "Finished in " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << endl;

    return 0;
}

int day3_part2_newMethod(){
    cout << "Running Day 3 Part 2 New Method..." << endl;
    auto start = std::chrono::steady_clock::now();
    //open file
    ifstream inFile("day3/input.txt");
    if(!inFile.is_open()){
        cout << "Could not open file" << endl;
        return -1;
    }

    vector<string> sacks;
    string currSack;

    inFile >> currSack;
    while(!inFile.eof()){
        sacks.push_back(currSack);
        inFile >> currSack;
    }

    inFile.close();

    int totalPriority = 0;

    //Try without using sets
    for(unsigned long i = 0; i < sacks.size(); i +=3){
        string s1;
        string s2;
        for(char item : sacks.at(i)){
            auto found = s1.find(item);
            if(found == string::npos){ //if the char is not in the string
                s1.push_back(item);
            }
        }
        for (char item : sacks.at(i+1)) {
            auto found = s2.find(item);
            if(found == string::npos){
                s2.push_back(item);
            }
        }
        for (char item : sacks.at(i+2)){
            auto find1 = s1.find(item);
            auto find2 = s2.find(item);
            if(find1 != string::npos && find2 != string::npos){
                if(item >= 'a'){
                    item -= 96;
                    totalPriority += item;
                }
                else if(item >= 'A'){
                    item = item - 64 + 26;
                    totalPriority += item;
                }
                break;
            }
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;

    cout << "Total priority for part 2 new method is: " << totalPriority << endl;
    cout << "Finished in " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << endl;

    return 0;
}