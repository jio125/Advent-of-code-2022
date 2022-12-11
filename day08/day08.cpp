#include "day08.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using std::cin, std::cout, std::endl;
using std::ifstream;
using std::vector;
using std::string;

#define CHAR_TO_INT(x)  x-'0'

int day8_part1(){
    cout << "Running Day 8 Part 1..." << endl;
    auto start = std::chrono::steady_clock::now();
    ifstream inFile("day08/input.txt");
    if(!inFile.is_open()){
        cout << "Could not open file." << endl;
        return -1;
    }

    vector<vector<int>> heightMap;

    //read file
    string currLine;
    getline(inFile, currLine);
    while (!inFile.eof()){
        vector<int> currRow;
        for(char ch : currLine){
            currRow.push_back(CHAR_TO_INT(ch));
        }
        heightMap.push_back(currRow);
        getline(inFile, currLine);
    }

    int numVisible = 0; //Count how many trees are visible
    
    //Loop through map to find visible trees
    for(int row = 0; row < heightMap.size(); row++){ //Could use for-each, but this method lets us use the index
        for(int col = 0; col < heightMap.at(row).size(); col++){
            //check visibility from the top
            bool visibleFromTop = true;
            for(int rowToCheck = row - 1; rowToCheck >= 0; rowToCheck--){
                if(heightMap.at(rowToCheck).at(col) >= heightMap.at(row).at(col)){
                    visibleFromTop = false;
                    break;
                }
            }
            if(visibleFromTop){
                numVisible++;
                continue; //move to next tree
            }

            //check visibility from the bottom
            bool visibleFromBot = true;
            for(int rowToCheck = row + 1; rowToCheck < heightMap.size(); rowToCheck++){
                if(heightMap.at(rowToCheck).at(col) >= heightMap.at(row).at(col)){
                    visibleFromBot = false;
                    break;
                }
            }
            if(visibleFromBot){
                numVisible++;
                continue; //move to next tree
            }

            //check visibility from the left
            bool visibleFromLeft = true;
            for(int colToCheck = col - 1; colToCheck >= 0; colToCheck--){
                if(heightMap.at(row).at(colToCheck) >= heightMap.at(row).at(col)){
                    visibleFromLeft = false;
                    break;
                }
            }
            if(visibleFromLeft){
                numVisible++;
                continue; //move to next tree
            }

            //check visibility from the right
            bool visibleFromRight = true;
            for(int colToCheck = col + 1; colToCheck < heightMap.at(row).size(); colToCheck++){
                if(heightMap.at(row).at(colToCheck) >= heightMap.at(row).at(col)){
                    visibleFromRight = false;
                    break;
                }
            }
            if(visibleFromRight){
                numVisible++;
                continue; //move to next tree
            }
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;

    cout << "Number of trees visible from the outside is: " << numVisible << endl;
    cout << "Finished in " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << endl;

    return 0;
}

int day8_part2(){
    cout << "Running Day 8 Part 2..." << endl;
    auto start = std::chrono::steady_clock::now();
    ifstream inFile("day08/input.txt");
    if(!inFile.is_open()){
        cout << "Could not open file." << endl;
        return -1;
    }

    vector<vector<int>> heightMap;

    //read file
    string currLine;
    getline(inFile, currLine);
    while (!inFile.eof()){
        vector<int> currRow;
        for(char ch : currLine){
            currRow.push_back(CHAR_TO_INT(ch));
        }
        heightMap.push_back(currRow);
        getline(inFile, currLine);
    }

    vector<int> visScores;
    
    //Loop through map to find visible trees
    for(int row = 0; row < heightMap.size(); row++){ //Could use for-each, but this method lets us use the index
        for(int col = 0; col < heightMap.at(row).size(); col++){
            //check visibility score from the top
            int visScoreTop = row;
            for(int rowToCheck = row - 1; rowToCheck >= 0; rowToCheck--){
                if(heightMap.at(rowToCheck).at(col) >= heightMap.at(row).at(col)){
                    visScoreTop = row - rowToCheck;
                    if(visScoreTop < 0) visScoreTop = -visScoreTop;
                    break;
                }
            }
            
            //check visibility score from the bottom
            int visScoreBot = heightMap.size() - row - 1;
            for(int rowToCheck = row + 1; rowToCheck < heightMap.size(); rowToCheck++){
                if(heightMap.at(rowToCheck).at(col) >= heightMap.at(row).at(col)){
                    visScoreBot = rowToCheck - row;
                    if(visScoreBot < 0) visScoreBot = -visScoreBot;
                    break;
                }
            }

            //check visibility score from the left
            int visScoreLeft = col;
            for(int colToCheck = col - 1; colToCheck >= 0; colToCheck--){
                if(heightMap.at(row).at(colToCheck) >= heightMap.at(row).at(col)){
                    visScoreLeft = col - colToCheck;
                    if(visScoreLeft < 0) visScoreLeft = -visScoreLeft;
                    break;
                }
            }

            //check visibility score from the right
            int visScoreRight = heightMap.at(row).size() - col - 1;
            for(int colToCheck = col + 1; colToCheck < heightMap.at(row).size(); colToCheck++){
                if(heightMap.at(row).at(colToCheck) >= heightMap.at(row).at(col)){
                    visScoreRight = colToCheck - col;
                    if(visScoreRight < 0) visScoreRight = -visScoreRight;
                    break;
                }
            }
            int visScore = visScoreTop * visScoreBot * visScoreLeft * visScoreRight;
            visScores.push_back(visScore);
        }
    }

    int max = 0;
    for(int score : visScores){
        if(score > max){
            max = score;
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;

    cout << "Max visibility score is: " << max << endl;
    cout << "Finished in " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << endl;

    return 0;
}

int day8_all(){
    day8_part1();
    day8_part2();
    return 0;
}