#include <vector>
#include <iostream>
#include <sstream>
#include <stdexcept>

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
    //cerr << "Read\n";
    int tempword;
    cin >> tempword;
    //cerr << tempword << endl;
    if (instructmemloc >= 0 && instructmemloc < mainmemory->size()) {
        if (!cin) {
            cerr << "error: invalid input. Expected an integer.\n";
            cout << "error: invalid input. Expected an integer.\n";

        }
        (*mainmemory)[instructmemloc] = tempword;
    }
    else {
        cerr << "error: memory location out of bounds.\n";
        cout << "error: memory location out of bounds.\n";
    }
}

void WRITE(int instructmemloc, vector<int>* mainmemory) {
    //cerr << "Write\n";
    if (instructmemloc >= 0 && instructmemloc < mainmemory->size()) {
        cout << (*mainmemory)[instructmemloc];
    }
    else {
        cerr << "error: memory location out of bounds.\n";
        cout << "error: memory location out of bounds.\n";
    }
}


// Test functions
void test_READ() {
    // Initialize memory
    cerr << "Beginning read test\n";
    vector<int> memory(10, 0);

    // Test valid location (within bounds)
    input.str("42");
    cerr << "valid location test\n";
    READ(5, &memory);
    if (memory[5] != 42) {
        cerr << "error: read test failed (valid location)." << endl;
    }
    cerr << "valid location test complete\n\n";
    
    // Test invalid location (out of bounds)
    input.str("100");
    cerr << "invalid location test\n";
    output.str("");  // Reset output stream
    READ(15, &memory);
    if (output.str() != "error: memory location out of bounds.\n") {
        cerr << "error: read test failed (out of bounds)." << endl;
    }
    cerr << "invalid location test complete\n\n";

    // Test invalid input (non-integer)
    input.str("invalid");
    cerr << "invalid input type test\n";
    output.str("");  // Reset output stream
    READ(3, &memory);
    if (output.str() != "error: invalid input. Expected an integer.\n") {
        cerr << "error: read test failed (invalid input)." << endl;
    }
    cerr << "invalid input type test complete\n\n";
    
}

void test_WRITE() {
    // Initialize memory
    cerr << "Beginning write test\n";
    vector<int> memory(10, 0);
    memory[5] = 42;

    // Test valid location (within bounds)
    output.str("");  // Reset output stream
    cerr << "valid location test\n";
    WRITE(5, &memory);
    if (output.str() != "42") {
        cerr << "error: write test failed (valid location)." << endl;
    }
    cerr << "valid location test complete\n\n";

    // Test invalid location (out of bounds)
    output.str("");  // Reset output stream
    cerr << "invalid location test\n";
    WRITE(15, &memory);
    if (output.str() != "error: memory location out of bounds.\n") {
        cerr << "error: write test failed (out of bounds)." << endl;
    }
    cerr << "invalid location test complete\n\n";
}

int main() {
    // Run the test functions
    test_READ();
    test_WRITE();

    return 0;
}
