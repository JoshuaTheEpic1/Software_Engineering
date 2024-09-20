#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <vector>
using namespace std;

void loadWord(int* accumptr, vector<int> *mainMemory, int instructMemLoc);

void storeWord(int* accumptr, vector<int> *mainMemory, int instructMemLoc);

int UNITTESTING();

//functions from main.cpp
void openFile(vector<string>* instruct, vector<int>* memLocations);
void doInstruction(string instruct,  vector<int>* mainMemory, int instructMemLoc, int* accumptr, int* currMemLoc);

#endif