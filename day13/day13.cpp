#include "day13.h"

#include <iostream>
using std::cout, std::endl;
#include <fstream>
using std::ifstream;
#include <string>
using std::string;
#include <algorithm>
using std::replace;
#include <vector>
using std::vector;
#include <sstream>
using std::stringstream;

enum dataType{
    list,
    num
};

struct listItem{
    dataType type;
    int val = -1; //value if it is a number
    vector<listItem> data; //list if it is a list
    bool operator<(listItem& right){
        if(type == list && right.type == list){ //compare lists
            for(int i = 0; i < data.size(); i++){
                if(i >= right.data.size()) return false; //right side ran out of items first
                if(data.at(i) < right.data.at(i)) return true;
                if(data.at(i) == right.data.at(i)) continue;
                return false;
            }
            if(data.size() == right.data.size()) return false; //lists are equal not less
            return true; //left side ran out of items first
        }
        else if(type == num && right.type == num){ //compare ints
            return (val < right.val);
        }
        else{ // compare list vs int
            if(type == num){ //convert this to list
                // return (val < right.data.at(0).val);
                type = list;
                listItem n  = {.type = num};
                n.val = val;
                data.push_back(n);
                return (*this < right);
            }
            else{ // convert right to list
                // return (data.at(0).val < right.val);
                right.type = list;
                listItem n = {.type = num};
                n.val = right.val;
                right.data.push_back(n);
                return (*this < right);
            }
        }
    }
    bool operator>(listItem& right){
        if(type == list && right.type == list){ //compare lists
            for(int i = 0; i < data.size(); i++){
                if(i >= right.data.size()) return false; //right side ran out of items first
                if(data.at(i) > right.data.at(i)) return true;
                if(data.at(i) == right.data.at(i)) continue;
                return false;
            }
            if(data.size() == right.data.size()) return false; //lists are equal not less
            return true; //left side ran out of items first
        }
        else if(type == num && right.type == num){ //compare ints
            return (val > right.val);
        }
        else{ // compare list vs int
            if(type == num){ //convert this to list
                type = list;
                listItem n  = {.type = num};
                n.val = val;
                data.push_back(n);
                return (*this > right);
            }
            else{ // convert right to list
                right.type = list;
                listItem n = {.type = num};
                n.val = right.val;
                right.data.push_back(n);
                return (*this > right);
            }
        }
    }
    bool operator==(listItem& right){
        if(type == list && right.type == list){ //compare lists
            if(data.size() != right.data.size()) return false; //not the same size
            for(int i = 0; i < data.size(); i++){
                if(data.at(i) == right.data.at(i)) continue;
                return false;
            }
            return true;
        }
        else if(type == num && right.type == num){ //compare ints
            return (val == right.val);
        }
        else{ // compare list vs int
            if(type == num){ //convert this to list
                // return (val < right.data.at(0).val);
                type = list;
                listItem n  = {.type = num};
                n.val = val;
                data.push_back(n);
                return (data.at(0) == right.data.at(0));
            }
            else{ // convert right to list
                // return (data.at(0).val < right.val);
                right.type = list;
                listItem n = {.type = num};
                n.val = right.val;
                right.data.push_back(n);
                return (data.at(0) == right.data.at(0));
            }
        }
    }
};

void parse(stringstream& line, listItem& packet){
    while(true){
        char ch;
        line >> ch;
        if(ch == '['){
            listItem item = {.type = list};
            parse(line, item);
            packet.data.push_back(item);
        }
        else if(ch == ']'){ // end of sub-packet
            return;
        }
        else{ // number
            listItem item = {.type = num};
            line.putback(ch);
            int n;
            line >> n;
            item.val = n;
            packet.data.push_back(item);
        }
    }
}

int day13_part1(){
    cout << "Running Day 13 Part 1..." << endl;
    ifstream inFile("../day13/input.txt");
    if(!inFile.is_open()){
        cout << "Could not open file" << endl;
        return -1;
    }

    string currLine;
    int packetIndex = 1;
    int indexSum = 0;
    getline(inFile, currLine);
    while(!inFile.eof()){
        replace(currLine.begin(), currLine.end(), ',', ' '); //replace commas with a space
        listItem left = {.type = list}; //create left as a list type
        stringstream line(currLine);
        line.ignore(1); // skip first open bracket
        parse(line, left);
        getline(inFile, currLine);
        replace(currLine.begin(), currLine.end(), ',', ' ');
        stringstream line2(currLine);
        line2.ignore(1);
        listItem right = {.type = list};
        parse(line2, right);
        if(left < right){
            indexSum += packetIndex;
        }
        packetIndex++;
        getline(inFile, currLine); // skip blank line
        getline(inFile, currLine);
    }

    cout << "Sum of packet indexes that are in the right order: " << indexSum << endl;

    return 0;
}

int day13_part2(){
    return 0;
}

int day13_all(){
    day13_part1();
    day13_part2();
    return 0;
}