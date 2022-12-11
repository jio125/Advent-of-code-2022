//
// Created by Jiovanni Ortiz-Anglero on 12/1/22.
//

#include "elf.h"

void elf::addItem(int cals) {
    items.push_back(cals);
}

int elf::getSum() {
    int sum = 0;
    for(int item : items){
        sum += item;
    }
    return sum;
}
