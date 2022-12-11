#ifndef ROPE_H
#define ROPE_H

#include <vector>

using std::vector;

#define ABS(x) ((x > 0) ? (x) : -(x))

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

#endif //ROPE_H