#include <vector>
#include <string>
#include "mainMemory.h"


MainMemory::MainMemory(){
    this->mainMemory.resize(250);
}
MainMemory::MainMemory(int size){
    this->mainMemory.resize(size);
}
void MainMemory::setAll(std::vector<int> memory, int currMemLoc, int accumulator){
    this->mainMemory = memory;
    this->currMemLoc = currMemLoc;
    this->accumulator = accumulator;
}
