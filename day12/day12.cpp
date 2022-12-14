#include "day12.h"
//Standard library imports 
#include <iostream>
using std::cout, std::endl;
#include <fstream>
using std::ifstream;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <list>
using std::list;
#include <set>
using std::set;
#include <utility>
using std::pair;
#include <chrono>

struct Coordinate{
    int x = -1;
    int y = -1;
};

class Graph{
private:
    int numNodes;
    struct Edge{
        int dest = -1; //destination
        int weight = INT_MAX;
    };
    struct Node{
        list<Edge> edges; //List of this nodes edges
    };
    vector<Node> nodes;
    struct Dijkstra{
        int distance = INT_MAX;
        int pred = -1;
    };
    void computeDistances(vector<Dijkstra>&, int);
public:
    Graph(int n) : numNodes(n), nodes(n) {}
    ~Graph() = default;
    void addEdge(int v1, int v2, int weight);
    vector<int> shortestPath(int from, int to);
};

void Graph::addEdge(int v1, int v2, int weight = 1){
    Edge e1 = {v2, weight};
    nodes.at(v1).edges.push_back(e1);
}

vector<int> Graph::shortestPath(int from, int to){
    vector<int> path;
    vector<Dijkstra> distances(numNodes);
    computeDistances(distances, from);
    vector<int> revpath;
    int p = to;
    revpath.push_back(to);
    while ((p != -1) && (p != from)) {
        p = distances.at(p).pred;
        revpath.push_back(p);
    }
    if (p == -1) return path;
    for (int i = (int) (revpath.size()) - 1; i >= 0; --i) {
        path.push_back(revpath.at(i));
    }
    return path;
}

void Graph::computeDistances(vector<Dijkstra> &distances, int start){
    set<pair<int, int>> unvisited;   // pair = < distance, vertex >

    distances.at(start).distance = 0;
    unvisited.insert({0, start});

    while (!unvisited.empty()) {
        auto current = unvisited.begin();   // first element is minimum
        int vdist = current->first;
        int v = current->second;            // vertex
        unvisited.erase(current);
        for (auto const &edge: nodes.at(v).edges) {
            int newdist = vdist + edge.weight;
            int olddist = distances.at(edge.dest).distance;
            if ((olddist == INT_MAX) || (newdist < olddist)) {
                distances.at(edge.dest).distance = newdist;
                distances.at(edge.dest).pred = v;
                auto old = unvisited.find({olddist, edge.dest});
                if (old != unvisited.end()) unvisited.erase(old);
                unvisited.insert({newdist, edge.dest});
            }
        }
    }
}

int day12_part1(){
    cout << "Running day 12 Part 1..." << endl;
    auto startTime = std::chrono::steady_clock::now();
    ifstream inFile("day12/input.txt");
    if(!inFile.is_open()){
        cout << "Could not open file" << endl;
        return -1;
    }

    string currLine;
    vector<vector<char>> grid; //Store height map as a grid of chars
    getline(inFile, currLine);

    while(!inFile.eof()){
        vector<char> row;
        for(char ch : currLine){
            row.push_back(ch);
        }
        grid.push_back(row);
        getline(inFile, currLine);
    }

    //find start and end
    int start, end;
    for(int y = 0; y < grid.size(); y++){
        for(int x = 0; x < grid.at(y).size(); x++){
            if(grid.at(y).at(x) == 'S') {grid.at(y).at(x) = 'a'; start = (y*grid.at(y).size()) + x;} 
            else if(grid.at(y).at(x) == 'E') {grid.at(y).at(x) = 'z'; end = (y*grid.at(y).size()) + x;}
        }
    }

    Graph g(grid.size() * grid.at(0).size());
    //Add edges to graph
    
    for(int y = 0; y < grid.size(); y++){
        for(int x = 0; x < grid.at(y).size(); x++){
            char height = grid.at(y).at(x);
            //check if up is a neighbor
            if(y-1 >= 0){
                if(height - grid.at(y-1).at(x) >= char(-1)) g.addEdge((y*grid.at(y).size())+x, ((y-1)*grid.at(y-1).size())+x);
            }
            //check if down is a neighbor
            if(y+1 < grid.size()){
                if(height - grid.at(y+1).at(x) >= char(-1)) g.addEdge((y*grid.at(y).size())+x, ((y+1)*grid.at(y+1).size())+x);
            }
            //check if left is a neighbor
            if(x-1 >= 0){
                if(height - grid.at(y).at(x-1) >= char(-1)) g.addEdge((y*grid.at(y).size())+x, ((y)*grid.at(y).size())+(x-1));
            }
            //check if right is a neighbor
            if(x+1 < grid.at(y).size()){
                if(height - grid.at(y).at(x+1) >= char(-1)) g.addEdge((y*grid.at(y).size())+x, ((y)*grid.at(y).size())+(x+1));
            }
        }
    }

    auto path = g.shortestPath(start, end);
    int numSteps = path.size() - 1;

    auto endTime = std::chrono::steady_clock::now();
    auto diff = endTime - startTime;

    cout << "Minimun steps between start and end = " << numSteps << endl;
    cout << "Finished in " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << endl;

    return 0;
}

int day12_part2(){
    cout << "Running day 12 Part 2..." << endl;
    auto startTime = std::chrono::steady_clock::now();
    ifstream inFile("day12/input.txt");
    if(!inFile.is_open()){
        cout << "Could not open file" << endl;
        return -1;
    }

    string currLine;
    vector<vector<char>> grid; //Store height map as a grid of chars
    getline(inFile, currLine);

    while(!inFile.eof()){
        vector<char> row;
        for(char ch : currLine){
            row.push_back(ch);
        }
        grid.push_back(row);
        getline(inFile, currLine);
    }

    //find start and end
    int end;
    vector<int> startPoints;
    for(int y = 0; y < grid.size(); y++){
        for(int x = 0; x < grid.at(y).size(); x++){
            if(grid.at(y).at(x) == 'S') grid.at(y).at(x) = 'a'; 
            if(grid.at(y).at(x) == 'E') {grid.at(y).at(x) = 'z'; end = (y*grid.at(y).size()) + x;}
            if(grid.at(y).at(x) == 'a') startPoints.push_back((y*grid.at(y).size()) + x);
        }
    }

    Graph g(grid.size() * grid.at(0).size());
    //Add edges to graph
    
    for(int y = 0; y < grid.size(); y++){
        for(int x = 0; x < grid.at(y).size(); x++){
            char height = grid.at(y).at(x);
            //check if up is a neighbor
            if(y-1 >= 0){
                if(height - grid.at(y-1).at(x) >= char(-1)) g.addEdge((y*grid.at(y).size())+x, ((y-1)*grid.at(y-1).size())+x);
            }
            //check if down is a neighbor
            if(y+1 < grid.size()){
                if(height - grid.at(y+1).at(x) >= char(-1)) g.addEdge((y*grid.at(y).size())+x, ((y+1)*grid.at(y+1).size())+x);
            }
            //check if left is a neighbor
            if(x-1 >= 0){
                if(height - grid.at(y).at(x-1) >= char(-1)) g.addEdge((y*grid.at(y).size())+x, ((y)*grid.at(y).size())+(x-1));
            }
            //check if right is a neighbor
            if(x+1 < grid.at(y).size()){
                if(height - grid.at(y).at(x+1) >= char(-1)) g.addEdge((y*grid.at(y).size())+x, ((y)*grid.at(y).size())+(x+1));
            }
        }
    }

    int minSteps = INT_MAX;
    for(auto& start : startPoints){
        auto path = g.shortestPath(start, end);
        if(path.size() == 0) continue; // ignore paths that do not reach the end
        int steps = path.size() - 1;
        if(steps < minSteps) minSteps = steps;
    }

    auto endTime = std::chrono::steady_clock::now();
    auto diff = endTime - startTime;

    cout << "Minimun steps between start and end = " << minSteps << endl;
    cout << "Finished in " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << endl;

    return 0;
}

int day12_all(){
    day12_part1();
    day12_part2();
    return 0;
}