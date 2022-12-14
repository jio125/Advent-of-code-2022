#include "day11.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <numeric> //used for lcm
#include <chrono>

using std::cin, std::cout, std::endl;
using std::ifstream;
using std::vector;
using std::list;
using std::string;
using std::stringstream;
using std::lcm;

enum op{
    add,
    multiply,
    square
};

class Monkey{
private:
    list<unsigned long long> items;
    op opCode;
    int opVal;
    int testVal;
    int trueTarget;
    int falseTarget;
    int reduceMod;
    vector<Monkey*>* monkeyList;
    int numInspected;
    bool part2; //set to true for part 2, false for part 1
public:
    Monkey(vector<Monkey*>* monkeys) : monkeyList(monkeys), numInspected(0), part2(false) {}
    void addItem(unsigned long long item) {items.push_back(item);}
    void setOpcode(op opCode_) {opCode = opCode_;}
    void setOpVal(int val) {opVal = val;}
    void setTestVal(int val) {testVal = val;}
    int getTestVal() {return testVal;}
    void setTrueTarget(int target) {trueTarget = target;}
    void setFalseTarget(int target) {falseTarget = target;}
    void setReduceMod(int val) {reduceMod = val;}
    void setPart2() {part2 = true;}
    void inspect();
    int getNumInspected() {return numInspected;}
};

void Monkey::inspect(){
    int numItems = items.size();
    for(int i = 0; i < numItems; i++){ //inspect each item in queue
        unsigned long long item = items.front(); items.pop_front(); //get first item in queue and remove it from queue
        switch(opCode){ //inspect item
            case add: //add to worry value
                item += opVal;
                break;
            case multiply: //multiply worry val
                item *= opVal;
                break;
            case square: //square worry val
                item *= item;
                break;
        }
        if(!part2) item = item / 3; //divide worry level by 3 after inspection
        else item = item % reduceMod; //Reduce value while keeping the correct divisibility to prevent integer overflow
        if(item % testVal == 0){ //find which monkey to throw item to next
            monkeyList->at(trueTarget)->addItem(item);
        }
        else{
            monkeyList->at(falseTarget)->addItem(item);
        }
        numInspected++;
    }
}

int day11_part1(){
    cout << "Running Day 11 Part 1..." << endl;
    auto start = std::chrono::steady_clock::now();
    ifstream inFile("day11/input.txt");
    if(!inFile.is_open()){
        cout << "Could not open file." << endl;
        return -1;
    }

    vector<Monkey*> monkeys;
    
    //Read file
    string currLine;
    getline(inFile, currLine); //read "Monkey 0:" line

    while (!inFile.eof()){ // read file
        auto m = new Monkey(&monkeys);
        monkeys.push_back(m);
        getline(inFile, currLine); // Items line
        stringstream itemLine(currLine);
        string tmpstr;
        char tmpchar;
        unsigned long long item;
        itemLine >> tmpstr >> tmpstr;
        while(!itemLine.eof()){
            itemLine >> item;
            m->addItem(item);
            itemLine >> tmpchar;
        }
        getline(inFile, currLine); //operation line
        stringstream opLine(currLine);
        opLine >> tmpstr >> tmpstr >> tmpstr >> tmpstr; // skip first 4 words
        opLine >> tmpchar; //read operation
        opLine >> tmpstr;
        if(tmpstr == "old"){
            m->setOpcode(square);
        }
        else if(tmpchar == '*'){
            m->setOpcode(multiply);
            m->setOpVal(atoi(tmpstr.c_str()));
        }
        else if(tmpchar == '+'){
            m->setOpcode(add);
            m->setOpVal(atoi(tmpstr.c_str()));
        }
        getline(inFile, currLine);//test line
        stringstream testLine(currLine);
        testLine >> tmpstr >> tmpstr >> tmpstr; // skip first 3 words
        int val;
        testLine >> val;
        m->setTestVal(val);
        getline(inFile, currLine); //true line
        m->setTrueTarget((currLine.at(29) - '0'));
        getline(inFile, currLine); //false line
        m->setFalseTarget((currLine.at(30) - '0'));
        getline(inFile, currLine); // newline
        getline(inFile, currLine); // Monkey X: line
    }
    

    for(int i = 0; i < 20; i++){// run 20 rounds
        for(auto& monkey : monkeys){
            monkey->inspect();
        }
    }

    int max = 0;
    int second = 0;
    for(auto& monkey : monkeys){
        if(monkey->getNumInspected() > max){
            second = max;
            max = monkey->getNumInspected();
        }
        else if(monkey->getNumInspected() > second){
            second = monkey->getNumInspected();
        }
    }

    int monkeyBusiness = max * second;

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;

    cout << "Total monkey business: " << monkeyBusiness << endl;
    cout << "Finished in " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << endl;

    return 0;
}

int day11_part2(){
    cout << "Running Day 11 Part 2..." << endl;
    auto start = std::chrono::steady_clock::now();
    ifstream inFile("day11/input.txt");
    if(!inFile.is_open()){
        cout << "Could not open file." << endl;
        return -1;
    }

    vector<Monkey*> monkeys;
    
    //Read file
    string currLine;
    getline(inFile, currLine); //read "Monkey 0:" line

    while (!inFile.eof()){ // read file
        auto m = new Monkey(&monkeys);
        m->setPart2();
        monkeys.push_back(m);
        getline(inFile, currLine); // Items line
        stringstream itemLine(currLine);
        string tmpstr;
        char tmpchar;
        unsigned long long item;
        itemLine >> tmpstr >> tmpstr;
        while(!itemLine.eof()){
            itemLine >> item;
            m->addItem(item);
            itemLine >> tmpchar;
        }
        getline(inFile, currLine); //operation line
        stringstream opLine(currLine);
        opLine >> tmpstr >> tmpstr >> tmpstr >> tmpstr; // skip first 4 words
        opLine >> tmpchar; //read operation
        opLine >> tmpstr;
        if(tmpstr == "old"){
            m->setOpcode(square);
        }
        else if(tmpchar == '*'){
            m->setOpcode(multiply);
            m->setOpVal(atoi(tmpstr.c_str()));
        }
        else if(tmpchar == '+'){
            m->setOpcode(add);
            m->setOpVal(atoi(tmpstr.c_str()));
        }
        getline(inFile, currLine);//test line
        stringstream testLine(currLine);
        testLine >> tmpstr >> tmpstr >> tmpstr; // skip first 3 words
        int val;
        testLine >> val;
        m->setTestVal(val);
        getline(inFile, currLine); //true line
        m->setTrueTarget((currLine.at(29) - '0'));
        getline(inFile, currLine); //false line
        m->setFalseTarget((currLine.at(30) - '0'));
        getline(inFile, currLine); // newline
        getline(inFile, currLine); // Monkey X: line
    }
    
    //Calculate LCM of all test vals
    int leastCM = lcm(monkeys.at(0)->getTestVal(), monkeys.at(1)->getTestVal());
    for(int i = 2; i < monkeys.size(); i++){
        leastCM = lcm(leastCM, monkeys.at(i)->getTestVal());
    }
    //Set reduce mod for all monkeys
    for(auto& monkey : monkeys){
        monkey->setReduceMod(leastCM);
    }

    for(int i = 0; i < 10000; i++){// run 20 rounds
        for(auto& monkey : monkeys){
            monkey->inspect();
        }
    }

    unsigned long long max = 0;
    unsigned long long second = 0;
    for(auto& monkey : monkeys){
        if(monkey->getNumInspected() > max){
            second = max;
            max = monkey->getNumInspected();
        }
        else if(monkey->getNumInspected() > second){
            second = monkey->getNumInspected();
        }
    }

    unsigned long long monkeyBusiness = max * second;

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;

    cout << "Total monkey business: " << monkeyBusiness << endl;
    cout << "Finished in " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << endl;

    return 0;
}

int day11_all(){
    day11_part1();
    day11_part2();
    return 0;
}