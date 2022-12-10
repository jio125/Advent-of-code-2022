#include "day9.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

using std::cout, std::cin, std::endl;
using std::ifstream;
using std::vector;

#define ABS(x) ((x < 0) ? -x : x)

class Rope{
private:
    class Point{ //Stores coordinates
    public:
        int _x;
        int _y;
        Point() : _x(0), _y(0) {}
        Point(int x, int y) : _x(x), _y(y) {}
        bool operator==(const Point& other){
            if(_x == other._x && _y == other._y) return true;
            return false;
        }
    };
    vector<Point> knots;
    int numKnots;
    void moveKnots();
    vector<Point> visited;
public:
    Rope() : knots(2), numKnots(2) {visited.push_back(knots.at(1));}
    Rope(int numKnots_) : knots(numKnots_), numKnots(numKnots_) {visited.push_back(knots.at(numKnots_ - 1));}
    void moveHead(char direction, int spaces);
    int numVisited() {return visited.size();}
};


void Rope::moveHead(char direction, int spaces){
    for(int i = 0; i < spaces; i++){
        switch (direction)
        {
        case 'U':
            knots.at(0)._y++;
            break;
        case 'D':
            knots.at(0)._y--;
            break;
        case 'R':
            knots.at(0)._x++;
            break;
        case 'L':
            knots.at(0)._x--;
            break;
        default:
            break;
        }
        moveKnots();
    }
}

void Rope::moveKnots(){ //Can probably refactor this but thats for later
    for(int i = 1; i < numKnots; i++){
        if(knots.at(i - 1) == knots.at(i) || (ABS(knots.at(i - 1)._x - knots.at(i)._x) == 1 && knots.at(i - 1)._y == knots.at(i)._y) ||
        (ABS(knots.at(i - 1)._y - knots.at(i)._y) == 1 && knots.at(i - 1)._x == knots.at(i)._x) || (ABS(knots.at(i - 1)._x - knots.at(i)._x) == 1 && ABS(knots.at(i - 1)._y - knots.at(i)._y) == 1)){ //No movement needed
            continue;
        }
        if(knots.at(i - 1)._x == knots.at(i)._x || knots.at(i - 1)._y == knots.at(i)._y){ //Cardinal movement
            if(knots.at(i - 1)._x - knots.at(i)._x == 2){ // Move right
                knots.at(i)._x++;
            }
            else if(knots.at(i - 1)._x - knots.at(i)._x == -2){ //Move left
                knots.at(i)._x--;
            }
            else if(knots.at(i - 1)._y - knots.at(i)._y == 2){ //Move up
                knots.at(i)._y++;
            }
            else if(knots.at(i - 1)._y - knots.at(i)._y == -2){ //Move down
                knots.at(i)._y--;
            }
        }
        else { // Diagonal movement
            if((knots.at(i - 1)._x - knots.at(i)._x == 2 && knots.at(i - 1)._y - knots.at(i)._y == 1) || (knots.at(i - 1)._y - knots.at(i)._y == 2 && knots.at(i - 1)._x - knots.at(i)._x == 1) || (knots.at(i - 1)._y - knots.at(i)._y == 2 && knots.at(i - 1)._x - knots.at(i)._x == 2)){ //Move up and right one
                knots.at(i)._x++;
                knots.at(i)._y++;
            }
            else if((knots.at(i - 1)._x - knots.at(i)._x == -2 && knots.at(i - 1)._y - knots.at(i)._y == 1) || (knots.at(i - 1)._y - knots.at(i)._y == 2 && knots.at(i - 1)._x - knots.at(i)._x == -1) || (knots.at(i - 1)._y - knots.at(i)._y == 2 && knots.at(i - 1)._x - knots.at(i)._x == -2)){ //Move up and left one
                knots.at(i)._x--;
                knots.at(i)._y++;
            }
            else if((knots.at(i - 1)._x - knots.at(i)._x == 2 && knots.at(i - 1)._y - knots.at(i)._y == -1) || (knots.at(i - 1)._y - knots.at(i)._y == -2 && knots.at(i - 1)._x - knots.at(i)._x == 1) || (knots.at(i - 1)._y - knots.at(i)._y == -2 && knots.at(i - 1)._x - knots.at(i)._x == 2)){ //Move down and right one
                knots.at(i)._x++;
                knots.at(i)._y--;
            }
            else if((knots.at(i - 1)._x - knots.at(i)._x == -2 && knots.at(i - 1)._y - knots.at(i)._y == -1) || (knots.at(i - 1)._y - knots.at(i)._y == -2 && knots.at(i - 1)._x - knots.at(i)._x == -1) || (knots.at(i - 1)._y - knots.at(i)._y == -2 && knots.at(i - 1)._x - knots.at(i)._x == -2)){ //Move down and left left
                knots.at(i)._x--;
                knots.at(i)._y--;
            }
        }
    }
    bool visitedBefore = false;
    for(Point p : visited){
        if(p == knots.at(numKnots - 1)){
            visitedBefore = true;
            break;
        }
    }
    if(!visitedBefore) visited.push_back(knots.at(numKnots - 1));
}

int day9_part1(){
    cout << "Running Day 9 Part 1..." << endl;
    auto start = std::chrono::steady_clock::now();
    ifstream inFile("../day9/input.txt");
    if(!inFile.is_open()){
        cout << "Could not read file." << endl;
        return -1;
    }

    Rope g; //Rope with 2 knots (head and tail)

    char direction;
    int distance;

    inFile >> direction;
    inFile >> distance;

    while (!inFile.eof())
    {
        g.moveHead(direction, distance);
        inFile >> direction;
        inFile >> distance;
    }

    int numSpacesVisited = g.numVisited();
    

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;

    cout << "Number of spaces visited: " << numSpacesVisited << endl;

    cout << "Finished in " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << endl;

    return 0;
}

int day9_part2(){
    cout << "Running Day 9 Part 2..." << endl;
    auto start = std::chrono::steady_clock::now();
    ifstream inFile("../day9/input.txt");
    if(!inFile.is_open()){
        cout << "Could not read file." << endl;
        return -1;
    }

    Rope g(10); //Rope with 10 knots (head=0, tail=9)

    char direction;
    int distance;

    inFile >> direction;
    inFile >> distance;

    while (!inFile.eof())
    {
        g.moveHead(direction, distance);
        inFile >> direction;
        inFile >> distance;
    }

    int numSpacesVisited = g.numVisited();
    

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