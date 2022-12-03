//
// Created by Jiovanni Ortiz-Anglero on 12/3/22.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <set>
using std::set;
using std::vector;
using std::string;
using std::cout, std::cin, std::endl;
using std::ifstream;

int main(){
    //open file
    ifstream inFile("input.txt");
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

    auto start = std::chrono::steady_clock::now(); //start time

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

    auto end = std::chrono::steady_clock::now(); //end time
    auto diff = end - start;

    cout << "Total priority for part 1 is: " << totalPriority << endl;
    cout << std::chrono::duration<double,std::milli>(diff).count() << "ms to execute" << endl;

    //Part 2
    totalPriority = 0;

    start = std::chrono::steady_clock::now(); //start time

    for(int i = 0; i < sacks.size(); i +=3){
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

    end = std::chrono::steady_clock::now(); //end time
    diff = end - start;

    cout << endl << "Total priority for part 2 is: " << totalPriority << endl;
    cout << std::chrono::duration<double,std::milli>(diff).count() << "ms to execute" << endl;

    totalPriority = 0;
    start = std::chrono::steady_clock::now(); //start time

    //Try without using sets
    for(int i = 0; i < sacks.size(); i +=3){
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

    end = std::chrono::steady_clock::now(); //end time
    diff = end - start;

    cout << endl << "Total priority for part 2 new method is: " << totalPriority << endl;
    cout << std::chrono::duration<double,std::milli>(diff).count() << "ms to execute" << endl;

    return 0;
}