#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <vector>
using std::vector;
#include <string>
using std::string;

class file
{
private:
    string name;
    int size;
public:
    file() : name(""), size(0) {}
    file(string n, int s = 0) : name(n), size(s) {}
    void setName(string n) {name = n;}
    string getName() {return name;}
    void setSize(int s) {size = s;}
    int getSize() {return size;}
};

class directory
{
private:
    string name;
    directory* parentDirectory;
    vector<directory*> subDirectories;
    vector<file> files;
public:
    directory(string n, directory* parent = nullptr) : name(n), parentDirectory(parent) {}
    void addSubdirectory(directory*);
    void addFile(file);
    void setParent(directory*);
    directory* getParent() {return parentDirectory;}
    int getSize();
};


#endif //FILESYSTEM_H