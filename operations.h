#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <vector>
using namespace std;

void loadWord(int* accumptr, vector<int> *mainMemory, int instructMemLoc);

void storeWord(int* accumptr, vector<int> *mainMemory, int instructMemLoc);

int UNITTESTING();

#endif