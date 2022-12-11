#include "day09.h"
#include "rope.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

using std::cout, std::cin, std::endl;
using std::ifstream;
using std::vector;

int day9_part1(){
    cout << "Running Day 9 Part 1..." << endl;
    auto start = std::chrono::steady_clock::now();
    ifstream inFile("day09/input.txt");
    if(!inFile.is_open()){
        cout << "Could not read file." << endl;
        return -1;
    }

    Rope r; //Rope with 2 knots (head and tail)

    char direction;
    int distance;

    inFile >> direction;
    inFile >> distance;

    while (!inFile.eof())
    {
        r.moveHead(direction, distance);
        inFile >> direction;
        inFile >> distance;
    }

    int numSpacesVisited = r.numVisited();
    

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;

    cout << "Number of spaces visited: " << numSpacesVisited << endl;

    cout << "Finished in " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << endl;

    return 0;
}

int day9_part2(){
    cout << "Running Day 9 Part 2..." << endl;
    auto start = std::chrono::steady_clock::now();
    ifstream inFile("day09/input.txt");
    if(!inFile.is_open()){
        cout << "Could not read file." << endl;
        return -1;
    }

    Rope r(10); //Rope with 10 knots (head=0, tail=9)

    char direction;
    int distance;

    inFile >> direction;
    inFile >> distance;

    while (!inFile.eof())
    {
        r.moveHead(direction, distance);
        inFile >> direction;
        inFile >> distance;
    }

    int numSpacesVisited = r.numVisited();
    

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;

    cout << "Number of spaces visited: " << numSpacesVisited << endl;

    cout << "Finished in " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << endl;

    return 0;
}

int day9_all(){
    day9_part1();
    day9_part2();
    return 0;
}