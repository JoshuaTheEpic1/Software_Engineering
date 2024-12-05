#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "operations.h"
using namespace std;

// Initialize input and output string streams for testing
std::istringstream input; 
std::ostringstream output; 
bool unitTestPassed = true; // Flag to track if unit tests pass
MainMemory UnitTestingMemory; // Instance of MainMemory for unit testing

// Function to test loading a word into the accumulator
void workingLoadWord() {
    UnitTestingMemory.setAccumulator(0); // Reset accumulator to 0
    UnitTestingMemory.setMemoryLocation(0); // Set current memory location to 0
    // Initialize memory locations with test values
    UnitTestingMemory.setValueAt(0, 10);
    UnitTestingMemory.setValueAt(1, 20);
    UnitTestingMemory.setValueAt(2, 30);
    
    loadWord(&UnitTestingMemory, 1); // Load value from memory location 1 into the accumulator
    
    // Check if the accumulator has the expected value
    if (UnitTestingMemory.getAccumulator() == 20) {
        std::cout << "LoadWord test passed" << std::endl; // Test passed
    } else {
        std::cout << "LoadWord test failed: Expected " << UnitTestingMemory.getValueAt(1) 
                  << " but got " << UnitTestingMemory.getAccumulator() << std::endl; // Test failed
        unitTestPassed = false; // Mark test as failed
    }
}

// Function to test loading a word with an out-of-bounds memory location
void oobLoadWord() {
    std::vector<int> mainMemory; // Vector to simulate main memory
    int accumulator = 0; // Initialize accumulator
    int* accumptr = &accumulator; // Pointer to accumulator
    int currMemLoc = 0; // Current memory location
    mainMemory.resize(3); // Resize memory to hold 3 values
    mainMemory.at(0) = 10; // Set test values
    mainMemory.at(1) = 20;
    mainMemory.at(2) = 30;

    try {
        loadWord(&UnitTestingMemory, 101); // Attempt to load from an out-of-bounds location
        std::cout << "Out of bounds LoadWord test failed" << std::endl; // Test failed
    } catch (std::out_of_range const& e) {
        std::cout << "Out of bounds LoadWord test passed" << std::endl; // Test passed
    } catch (...) {
        std::cout << "Out of bounds LoadWord test failed: unexpected exception" << std::endl; // Unexpected exception
        unitTestPassed = false; // Mark test as failed
    }
}

// Function to test storing a word from the accumulator to memory
void workingStoreWord() {
    UnitTestingMemory.setAccumulator(0); // Reset accumulator to 0
    UnitTestingMemory.setMemoryLocation(0); // Set current memory location to 0
    UnitTestingMemory.setValueAt(0, 10); // Initialize memory locations with test values
    UnitTestingMemory.setValueAt(1, 20);
    
    loadWord(&UnitTestingMemory, 1); // Load value from memory location 1 into the accumulator
    storeWord(&UnitTestingMemory, 2); // Store the accumulator value into memory location 2
    
    // Check if the value was stored correctly
    if (UnitTestingMemory.getValueAt(2) == 20) {
        std::cout << "StoreWord test passed" << std::endl; // Test passed
    } else {
        std::cout << "StoreWord test failed: Expected " << UnitTestingMemory.getValueAt(1) 
                  << " but got " << UnitTestingMemory.getValueAt(2) << std::endl; // Test failed
        unitTestPassed = false; // Mark test as failed
    }
}

// Function to test storing a word with an out-of-bounds memory location
void oobStoreWord() {
    UnitTestingMemory.setAccumulator(0); // Reset accumulator to 0
    UnitTestingMemory.setMemoryLocation(0); // Set current memory location to 0
    UnitTestingMemory.setValueAt(0, 10); // Initialize memory locations with test values
    UnitTestingMemory.setValueAt(1, 20);

    try {
        storeWord(&UnitTestingMemory, 101); // Attempt to store to an out-of-bounds location
        std::cout << "Out of bounds StoreWord test failed: unexpected exception" << std::endl; // Test failed
    } catch (std::out_of_range const& e) {
        std::cout << "Out of bounds StoreWord test passed" << std::endl; // Test passed
    } catch (...) {
        std::cout << "Out of bounds StoreWord test failed: unexpected exception" << std::endl; // Unexpected exception
        unitTestPassed = false; // Mark test as failed
    }
}

// Function to test branching instructions (+40/-40)
void workingBranch() {
    UnitTestingMemory.setAccumulator(0); // Reset accumulator to 0
    UnitTestingMemory.setMemoryLocation(0); // Set current memory location to 0

    doInstruction(+40, 2, &UnitTestingMemory); // Branch to memory location 2
    // Check if the memory location was updated correctly
    if (UnitTestingMemory.getMemoryLocation() != 2) {
        std::cout << "Branch test workingBranch: failed change to correct location, location is: " 
                  << UnitTestingMemory.getMemoryLocation() << " should be 2." << std::endl; // Test failed
    } else {
        doInstruction(-40, 1, &UnitTestingMemory); // Branch back to memory location 1
        // Check if the memory location was updated correctly
        if (UnitTestingMemory.getMemoryLocation() != 1) {
            std::cout << "Branch test workingBranch: failed test 2 location is: " 
                      << UnitTestingMemory.getMemoryLocation() << " should be 1." << std::endl; // Test failed
            unitTestPassed = false; // Mark test as failed
        } else {
            std::cout << "Branch test workingBranch: Passed." << std::endl; // Test passed
        }
    }
}

// Function to test branching instructions (+41/-41) based on accumulator value
void workingBranchNegative() {
    UnitTestingMemory.setAccumulator(-10); // Set accumulator to a negative value
    UnitTestingMemory.setMemoryLocation(0); // Set current memory location to 0
    doInstruction(+41, 2, &UnitTestingMemory); // Branch to memory location 2

    // Check if the memory location was updated correctly
    if (UnitTestingMemory.getMemoryLocation() != 2) {
        std::cout << "Branch test workingBranchNegative: failed change to correct location, location is: " 
                  << UnitTestingMemory.getMemoryLocation() << " should be 2." << std::endl; // Test failed
        unitTestPassed = false; // Mark test as failed
    } else {
        UnitTestingMemory.setAccumulator(10); // Set accumulator to a positive value
        doInstruction(-41, 2, &UnitTestingMemory); // Attempt to branch to memory location 2

        // Check if the memory location was updated correctly
        if (UnitTestingMemory.getMemoryLocation() != 3) {
            std::cout << "Branch test workingBranchNegative: part 2, failed changed location when it shouldn't have, location is: " 
                      << UnitTestingMemory.getMemoryLocation() << " should be 2." << std::endl; // Test failed
            unitTestPassed = false; // Mark test as failed
        } else {
            std::cout << "Branch test WorkingBranchNegative: Passed." << std::endl; // Test passed
        }
    }
}

// Function to test branching instructions (+42/-42) based on accumulator being zero
void workingBranchZero() {
    UnitTestingMemory.setAccumulator(0); // Set accumulator to zero
    UnitTestingMemory.setMemoryLocation(0); // Set current memory location to 0
    doInstruction(+42, 2, &UnitTestingMemory); // Branch to memory location 2

    // Check if the memory location was updated correctly
    if (UnitTestingMemory.getMemoryLocation() != 2) {
        std::cout << "Branch test workingBranchZero: failed change to correct location, location is: " 
                  << UnitTestingMemory.getMemoryLocation() << " should be 2." << std::endl; // Test failed
        unitTestPassed = false; // Mark test as failed
    } else {
        UnitTestingMemory.setAccumulator(10); // Set accumulator to a non-zero value
        doInstruction(42, 2, &UnitTestingMemory); // Attempt to branch to memory location 2

        // Check if the memory location was updated correctly
        if (UnitTestingMemory.getMemoryLocation() != 3) {
            std::cout << "Branch test workingBranchZero: part 2, failed changed location when it shouldn't have, location is: " 
                      << UnitTestingMemory.getMemoryLocation() << " should be 2." << std::endl; // Test failed
            unitTestPassed = false; // Mark test as failed
        } else {
            std::cout << "Branch test workingBranchZero: Passed." << std::endl; // Test passed
        }
    }
}
/* // I'm not sure how to I can fix this test with our current GUI model.
void test_READ() {
    // Initialize memory

    cerr << "Beginning read test\n";
    vector<int> memory(10, 0);

    // Test valid location (within bounds)

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
    output << WRITE(5, &memory);
    if (output.str() != "42") {
        cout << endl <<  memory[5] << endl;
        cerr << "error: write test failed (valid location)." << endl;
    }
    cerr << "valid location test complete\n\n";

    // Test invalid location (out of bounds)
    output.str("");  // Reset output stream
    cerr << "invalid location test\n";
    output << WRITE(15, &memory);
    if (output.str() != "-1") {
        cerr << "error: write test failed (out of bounds)." << endl;
    }
    cerr << "invalid location test complete\n\n";
}*/
// Function to test the addition operation
void testAdd() {
    UnitTestingMemory.setAccumulator(10); // Set initial accumulator value to 10
    UnitTestingMemory.setMemoryLocation(0); // Set current memory location to 0
    UnitTestingMemory.setValueAt(2, 20); // Set memory location 2 to 20
    doInstruction(+30, 2, &UnitTestingMemory); // Perform addition operation (accumulator + memory[2])

    // Check if the accumulator has the expected value after addition
    if (UnitTestingMemory.getAccumulator() == 30) {
        std::cout << "First test add passed." << std::endl; // Test passed
        doInstruction(-30, 2, &UnitTestingMemory); // Perform the inverse operation
        // Check if the accumulator has the expected value after the second operation
        if (UnitTestingMemory.getAccumulator() == 50) {
            std::cout << "Second test add passed." << std::endl; // Test passed
        } else {
            std::cout << "Second test add failed. Should be 50 got: " 
                      << UnitTestingMemory.getAccumulator() << std::endl; // Test failed
            unitTestPassed = false; // Mark test as failed
        }
    } else {
        std::cout << "First test add failed. Should be 30 got: " 
                  << UnitTestingMemory.getAccumulator() << std::endl; // Test failed
        unitTestPassed = false; // Mark test as failed
    }
}

// Function to test the subtraction operation
void testSubtract() {
    UnitTestingMemory.setAccumulator(10); // Set initial accumulator value to 10
    UnitTestingMemory.setMemoryLocation(0); // Set current memory location to 0
    UnitTestingMemory.setValueAt(2, 20); // Set memory location 2 to 20
    doInstruction(+31, 2, &UnitTestingMemory); // Perform subtraction operation (accumulator - memory[2])

    // Check if the accumulator has the expected value after subtraction
    if (UnitTestingMemory.getAccumulator() == -10) {
        std::cout << "First test subtract passed." << std::endl; // Test passed
        doInstruction(-31, 2, &UnitTestingMemory); // Perform the inverse operation
        // Check if the accumulator has the expected value after the second operation
        if (UnitTestingMemory.getAccumulator() == -30) {
            std::cout << "Second test subtract passed." << std::endl; // Test passed
        } else {
            std::cout << "Second test subtract failed. Should be -10 got: " 
                      << UnitTestingMemory.getAccumulator() << std::endl; // Test failed
            unitTestPassed = false; // Mark test as failed
        }
    } else {
        std::cout << "First test subtract failed. Should be 0 got: " 
                  << UnitTestingMemory.getAccumulator() << std::endl; // Test failed
        unitTestPassed = false; // Mark test as failed
    }
}

// Function to test the division operation
void divideTests() {
    UnitTestingMemory.setMemoryLocation(0); // Set current memory location to 0
    UnitTestingMemory.setValueAt(2, 20); // Set memory location 2 to 20
    UnitTestingMemory.setValueAt(0, 10); // Set memory location 0 to 10
    UnitTestingMemory.setValueAt(1, 30); // Set memory location 1 to 30
    UnitTestingMemory.setValueAt(3, 0); // Set memory location 3 to 0 (for divide by zero test)

    // Test division: 50 / 10
    UnitTestingMemory.setAccumulator(50); // Set accumulator to 50
    DIVIDE(&UnitTestingMemory, 0); // Divide accumulator by value at memory location 0
    if (UnitTestingMemory.getAccumulator() == 5) {
        std::cout << "Divide test 50 / 10: Passed" << std::endl; // Test passed
    } else {
        std::cout << "Divide test 50 / 10: Failed" << std::endl; // Test failed
    }

    // Test divide by zero
    try {
        DIVIDE(&UnitTestingMemory, 3); // Attempt to divide by zero
    } catch (...) {
        if (UnitTestingMemory.getAccumulator() == 5) {
            std::cout << "Divide by zero test: Passed" << std::endl; // Test passed
        } else {
            std::cout << "Divide by zero test: Failed" << std::endl; // Test failed
            unitTestPassed = false; // Mark test as failed
        }
    }


}

// Function to test the multiplication operation
void multiplyTests() {
    UnitTestingMemory.setMemoryLocation(0); // Set current memory location to 0
    UnitTestingMemory.setValueAt(0, 10); // Set memory location 0 to 10
    UnitTestingMemory.setValueAt(1, 20); // Set memory location 1 to 20
    UnitTestingMemory.setValueAt(2, 30); // Set memory location 2 to 30
    UnitTestingMemory.setValueAt(3, 0); // Set memory location 3 to 0

    // Test multiplication: 5 * 20
    UnitTestingMemory.setAccumulator(5); // Set accumulator to 5
    MULTIPLY(&UnitTestingMemory, 1); // Multiply accumulator by value at memory location 1
    if (UnitTestingMemory.getAccumulator() == 100) { // Check if the result is correct
        std::cout << "Test 5 * 20: Passed" << std::endl; // Test passed
    } else {
        std::cout << "Test 5 * 20: Failed" << std::endl; // Test failed
        unitTestPassed = false; // Mark test as failed
    }

    // Test multiplication: 0 * 10
    UnitTestingMemory.setAccumulator(0); // Set accumulator to 0
    MULTIPLY(&UnitTestingMemory, 0); // Multiply accumulator by value at memory location 0
    if (UnitTestingMemory.getAccumulator() == 0) { // Check if the result is correct
        std::cout << "Test 0 * 10: Passed" << std::endl; // Test passed
    } else {
        std::cout << "Test 0 * 10: Failed" << std::endl; // Test failed
        unitTestPassed = false; // Mark test as failed
    }
}

// Function to run all unit tests
int UNITTESTING() {
    workingLoadWord(); // Run load word tests
    oobLoadWord(); // Run out-of-bounds load word tests
    workingStoreWord(); // Run store word tests
    oobStoreWord(); // Run out-of-bounds store word tests
    workingBranch(); // Run branch tests
    workingBranchNegative(); // Run negative branch tests
    workingBranchZero(); // Run zero branch tests
    divideTests(); // Run division tests
    multiplyTests(); // Run multiplication tests

    // Check if all tests passed
    if (unitTestPassed == true) {
        std::cout << "ALL TESTS PASS." << std::endl; // All tests passed
        return 1; // Return success
    } else {
        return 0; // Return failure
    }
}
