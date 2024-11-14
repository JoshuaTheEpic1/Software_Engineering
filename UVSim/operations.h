#ifndef OPERATIONS_H
#define OPERATIONS_H
#include <vector>
#include <string>
#include "mainMemory.h"
using namespace std;

void loadWord(MainMemory* mainMemory, int instructMemLoc);

void storeWord(MainMemory* mainMemory, int instructMemLoc);

int UNITTESTING();
void openFile(vector<string>* instruct, vector<int>* memLocations);
void doInstruction(int instruct, int instructMemLoc, MainMemory* mainMemory);
void READ(int instructMemLoc,  MainMemory* mainMemory, int value);
int WRITE(int instructMemLoc,  MainMemory* mainMemory);
void DIVIDE(MainMemory* mainMemory, int instructMemLoc);
void MULTIPLY(MainMemory* mainMemory, int instructMemLoc);
int Overflow(int value);

#endif

