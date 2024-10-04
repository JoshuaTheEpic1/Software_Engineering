#include <iostream>
#include <vector>
#include "operations.h"

// assign accumulator value to that of the given memory location
void loadWord(int* accumptr, vector<int>* mainMemory, int instructMemLoc){
    *accumptr = mainMemory->at(instructMemLoc);
}   

// store accumulator value into a given memory location
void storeWord( int* accumptr, vector<int> *mainMemory, int instructMemLoc){
    mainMemory->at(instructMemLoc) = *accumptr;
    *accumptr = 0;
}