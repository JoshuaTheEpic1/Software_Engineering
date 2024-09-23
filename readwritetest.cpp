#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

// Function prototypes
void READ(int instructmemloc, vector<int>* mainmemory);
void WRITE(int instructmemloc, vector<int>* mainmemory);

// Mock input and output streams
istringstream input;
ostringstream output;

// Redirect cin and cout
#define cin input
#define cout output

// Function definitions
void READ(int instructmemloc, vector<int>* mainmemory) {
    int tempword;
    cin >> tempword;
    if (instructmemloc >= 0 && instructmemloc < mainmemory->size()) {
        (*mainmemory)[instructmemloc] = tempword;
    }
    else {
        cerr << "error: memory location out of bounds." << endl;
    }
}

void WRITE(int instructmemloc, vector<int>* mainmemory) {
    if (instructmemloc >= 0 && instructmemloc < mainmemory->size()) {
        cout << (*mainmemory)[instructmemloc];
    }
    else {
        cerr << "error: memory location out of bounds." << endl;
    }
}

int main() {
    vector<int> memory(10, 0);
    
    // Simulate input (you can replace this with actual input)
    input.str("42");

    // Execute READ and WRITE functions
    READ(5, &memory);
    WRITE(5, &memory);

    return 0;
}
