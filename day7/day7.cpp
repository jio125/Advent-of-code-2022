#include "day7.h"
#include "filesystem.h"

#include <iostream>
#include <fstream>
#include <vector>

using std::cin, std::cout, std::endl;
using std::fstream;
using std::vector;

int day7_part1(){
    fstream inFile("../day7/test.txt");
    if(!inFile.is_open()){
        cout << "Could not open file." << endl;
        return -1;
    }

    directory* root = new directory("root");
    directory* currDirectory = root;

    string currLine;

    getline(inFile, currLine);

    while(!inFile.eof()){
    //parse line
        if(currLine.at(0) == '$'){ //user command
            if(currLine.at(2) == 'c'){ //change directory command
                if(currLine.at(5) == '/'){ //go to the root directory
                    currDirectory = root;
                }
                else if(currLine.at(5) == '.'){ // move up a directory
                    currDirectory = currDirectory->getParent();
                }
                else{ //move to new subdirectory
                    string dirName = currLine.substr(5);
                    directory* newDir = new directory(dirName, currDirectory);
                    currDirectory->addSubdirectory(newDir);
                    currDirectory = newDir;
                }
            }
            else if(currLine.at(2) == 'l'){ // list command
                //dont need to do anything else
            }
        }
        else if(currLine.at(0) == 'd'){ //directory listing
            //dont need to do anything here
            //new directory object created when moving into it
        }
        else{ //file listing
            string fileName = currLine.substr(currLine.find(' '));
            string sizeStr;
            for(int i = 0; i < currLine.find(' '); i++){
                sizeStr.push_back(currLine.at(i));
            }
            int size = atoi(sizeStr.c_str());
            file newFile(fileName, size);
            currDirectory->addFile(newFile);
        }
        getline(inFile, currLine);
    }

    cout << "Done reading file." << endl;

    return 0;
}

int day7_part2(){

    return 0;
}

int day7_all(){
    day7_part1();
    day7_part2();
    return 0;
}