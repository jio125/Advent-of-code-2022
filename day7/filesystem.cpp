#include "filesystem.h"

void directory::addFile(file f) {
    files.push_back(f);
}

void directory::addSubdirectory(directory* dir){
    subDirectories.push_back(dir);
}

void directory::setParent(directory* dir){
    parentDirectory = dir;
}

int directory::getSize(){
    int sum = 0;

    if(!subDirectories.empty()){
        for(auto& dir : subDirectories){
            sum += dir->getSize();
        }
    }

    for(auto& f : files){
        sum += f.getSize();
    }

    return sum;

    return 0;
}