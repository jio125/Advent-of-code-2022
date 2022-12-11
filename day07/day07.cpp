#include "day07.h"
#include "filesystem.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using std::cin, std::cout, std::endl;
using std::ifstream;
using std::vector;

void searchFilesystem(directory* dir, vector<directory*> &foundDirectories){
    if(!dir->getSubdirectories().empty()){
        for(auto& subDirectory : dir->getSubdirectories()){
            searchFilesystem(subDirectory, foundDirectories);
        }
    }
    foundDirectories.push_back(dir);
    return;
}

directory* readFilesystem(ifstream &inFile){
    directory* root = new directory("/");
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

    return root;
}

int day7_part1(){
    cout << "Running Day 7 Part 1..." << endl;
    auto start = std::chrono::steady_clock::now();
    ifstream inFile("day07/input.txt");
    if(!inFile.is_open()){
        cout << "Could not open file." << endl;
        return -1;
    }

    directory* root = readFilesystem(inFile);

    vector<directory*> directories;
    int maxSize = 100000; 

    searchFilesystem(root, directories);

    int sum = 0;
    for(const auto& dir : directories){
        if(dir->getSize() <= maxSize){
            sum += dir->getSize();
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;

    cout << "Sum of directories with a maximum size of " << maxSize << ": " << sum << endl;
    cout << "Finished in " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << endl;

    return 0;
}

int day7_part2(){
    cout << "Running Day 7 Part 2..." << endl;
    auto start = std::chrono::steady_clock::now();
    ifstream inFile("day07/input.txt");
    if(!inFile.is_open()){
        cout << "Could not open file." << endl;
        return -1;
    }

    directory* root = readFilesystem(inFile);

    vector<directory*> directories;
    searchFilesystem(root, directories);

    int totalDiskSpace = 70000000;
    int diskSpaceRemaining = totalDiskSpace - root->getSize();
    int diskSpaceNeeded = 30000000;
    int minSizeToDelete = diskSpaceNeeded - diskSpaceRemaining;
    directory* dirToDelete = nullptr;

    for(const auto& dir : directories){
        if(dir->getSize() >= minSizeToDelete){
            if(dirToDelete && dirToDelete->getSize() > dir->getSize()){
                dirToDelete = dir;
            }
            else if(dirToDelete == nullptr){
                dirToDelete = dir;
            }
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;

    cout << "Size of directory to delete: " << dirToDelete->getSize() << endl;
    cout << "Finished in " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << endl;

    return 0;
}

int day7_all(){
    day7_part1();
    day7_part2();
    return 0;
}