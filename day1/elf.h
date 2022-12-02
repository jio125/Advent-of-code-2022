//
// Created by Jiovanni Ortiz-Anglero on 12/1/22.
//

#ifndef DAY1_ELF_H
#define DAY1_ELF_H

#include <vector>
using std::vector;

class elf {
private:
    vector<int> items;
public:
    void addItem(int cals);
    int getSum();
};


#endif //DAY1_ELF_H
