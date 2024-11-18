#include <vector>
#include <string>
#include "mainMemory.h"


// Constructor for MainMemory class
MainMemory::MainMemory() {
    this->mainMemory.resize(250); // Initialize mainMemory with a default size of 250
}

// Constructor for MainMemory class with a specified size
MainMemory::MainMemory(int size) {
    this->mainMemory.resize(size); // Initialize mainMemory with the specified size
}

// Function to set all values in the main memory
void MainMemory::setAll(std::vector<int> memory, int currMemLoc, int accumulator) {
    this->mainMemory = memory; // Copy the provided memory vector to mainMemory
    this->currMemLoc = currMemLoc; // Set the current memory location
    this->accumulator = accumulator; // Set the accumulator value
}
