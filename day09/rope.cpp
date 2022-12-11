#include "rope.h"


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

void Rope::moveKnots(){ 
    for(int i = 1; i < numKnots; i++){
        if(!((ABS(knots.at(i - 1)._x - knots.at(i)._x) > 1) || (ABS(knots.at(i - 1)._y - knots.at(i)._y) > 1))){ //No movement needed
            continue;
        }
        if(knots.at(i - 1)._x == knots.at(i)._x){ //Move up/down
            knots.at(i)._y += (knots.at(i - 1)._y > knots.at(i)._y) ? 1 : -1;
        }
        else if(knots.at(i - 1)._y == knots.at(i)._y){ // Move Left/Right
            knots.at(i)._x += (knots.at(i - 1)._x > knots.at(i)._x) ? 1 : -1;
        }
        else { // Diagonal movement
            knots.at(i)._x += (knots.at(i - 1)._x > knots.at(i)._x) ? 1 : -1;
            knots.at(i)._y += (knots.at(i - 1)._y > knots.at(i)._y) ? 1 : -1;
        }
    }
    //Add tail to list of visited coordinates if that coordinate is not in list
    bool visitedBefore = false;
    for(Point p : visited){
        if(p == knots.at(numKnots - 1)){
            visitedBefore = true;
            break;
        }
    }
    if(!visitedBefore) visited.push_back(knots.at(numKnots - 1));
}