#include <vector>
#include <string>
#include "mainMemory.h"


MainMemory::MainMemory(){
    this->mainMemory.resize(100);
}
MainMemory::MainMemory(int size){
    this->mainMemory.resize(size);
}
