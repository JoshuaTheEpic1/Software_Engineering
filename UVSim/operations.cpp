#include <iostream>
#include <vector>
#include "operations.h"
#include <fstream>
#include <sstream>
#include "mainMemory.h"

const bool UNITTESTINGBOOL = false; // Switch this to true for unit testing; currently unused in this file due to GUI integration

// Assign the accumulator value to that of the given memory location
void loadWord(MainMemory* mainMemory, int instructMemLoc) {
    mainMemory->setAccumulator(mainMemory->getValueAt(instructMemLoc)); // Load value from memory into the accumulator
}

// Store the accumulator value into a given memory location
void storeWord(MainMemory* mainMemory, int instructMemLoc) {
    mainMemory->setValueAt(instructMemLoc, mainMemory->getAccumulator()); // Store the accumulator value into memory
}

// Function to read a value into memory from an instruction
void READ(int instructMemLoc, MainMemory* mainMemory, int value) {
    int tempword; // Assumes all words are integers; alteration needed for dynamic data types
    if (UNITTESTINGBOOL) {
        std::istringstream testInput; // Create a string stream for testing
        testInput.str("42"); // Simulate input for testing
        testInput >> tempword; // Read the test input into tempword
    } else {
        /* Currently unneeded with input from GUI
        std::cout << "Enter the number you'd like to store in memory." << std::endl;
        std::cin >> tempword; // Uncomment for user input
        */
    }

    // Check if the instruction memory location is within bounds
    if (instructMemLoc >= 0 && instructMemLoc < mainMemory->getMemoryList().size()) {
        /*
        if (!std::cin) { // Ensure the inputted word is an integer
            std::cout << "error: invalid input. Expected an integer.\n";
        }
        */
        mainMemory->setValueAt(instructMemLoc, value); // Set the value at the specified memory location
    } else {
        std::cout << "error: memory location out of bounds.\n"; // Error message for out-of-bounds access
        throw runtime_error("Memory location out of bounds.");
    }
}

// Function to write the value from a memory location to the console
int WRITE(int instructMemLoc, MainMemory* mainMemory) {
    // Check if the instruction memory location is within bounds
    if (instructMemLoc >= 0 && instructMemLoc < mainMemory->getMemoryList().size()) {
        std::cout << "Memory location: " << instructMemLoc << " has: " << mainMemory->getValueAt(instructMemLoc) << " saved." << std::endl;
        return mainMemory->getValueAt(instructMemLoc); // Return the value at the specified memory location
    } else {
        std::cout << "error: memory location out of bounds.\n"; // Error message for out-of-bounds access
        throw runtime_error("Memory location out of bounds.");
    }
    return -1; // Return -1 to indicate an error
}

// Function to divide the accumulator by a value from memory
void DIVIDE(MainMemory* mainMemory, int instructMemLoc) {
    int divisor = mainMemory->getValueAt(instructMemLoc); // Get the divisor from memory
    if (divisor == 0) {
        std::cout << "Divide by zero error" << std::endl; // Error message for division by zero
        throw runtime_error("Math error: Attempted to divide by Zero\n");
    } else {
        mainMemory->setAccumulator(mainMemory->getAccumulator() / divisor); // Perform division and update the accumulator
    }
}

// Function to multiply the accumulator by a value from memory
void MULTIPLY(MainMemory* mainMemory, int instructMemLoc) {
    int product = mainMemory->getAccumulator() * mainMemory->getValueAt(instructMemLoc); // Calculate the product
    if (product > 999999 || product < -999999) {
        product = Overflow(product); // Handle overflow if necessary
    }
    mainMemory->setAccumulator(product); // Update the accumulator with the product
}

// Function to handle overflow for values exceeding limits
int Overflow(int value) {
    int reducer = -1999999; // Set the reducer for overflow adjustment
    if (value < -999999) {
        reducer *= -1; // Adjust reducer for negative overflow
    }
    // Adjust the value to fit within the allowed range
    while (value > 999999 || value < -999999) {
        value += reducer; // Increment or decrement the value
    }
    return value; // Return the adjusted value
}

// Function to execute an instruction based on its code
void doInstruction(int instruct, int instructMemLoc, MainMemory* mainMemory) {
    bool branched = false; // Prevents an extra count to the current memory location if branched is true
    switch (instruct) {
        case 10:
        case -10:
            READ(instructMemLoc, mainMemory, 10); // Call READ function
            std::cout << "Memory location: " << instructMemLoc << " has loaded: " << mainMemory->getValueAt(instructMemLoc) << "." << std::endl;
            break;
        case 11:
        case -11:
            WRITE(instructMemLoc, mainMemory); // Call WRITE function
            break;
        case 20:
        case -20:
            loadWord(mainMemory, instructMemLoc); // Load word into the accumulator
            std::cout << mainMemory->getAccumulator() << " is now in accumulator." << std::endl;
            break;
        case 21:
        case -21:
            storeWord(mainMemory, instructMemLoc); // Store accumulator value into memory
            std::cout << "Value at memory location " << instructMemLoc << " is now " << mainMemory->getValueAt(instructMemLoc) << "." << std::endl;
            break;
        case 30:
        case -30:
            std::cout << "Adding: " << mainMemory->getAccumulator() << " + " << mainMemory->getValueAt(instructMemLoc) << " = ";
            mainMemory->setAccumulator(mainMemory->getAccumulator() + mainMemory->getValueAt(instructMemLoc)); // Add value to accumulator
            std::cout << mainMemory->getAccumulator() << " which is now in the accumulator." << std::endl;
            break;
        case 31:
        case -31:
            std::cout << "Subtracting: " << mainMemory->getAccumulator() << " - " << mainMemory->getValueAt(instructMemLoc) << " = ";
            mainMemory->setAccumulator(mainMemory->getAccumulator() - mainMemory->getValueAt(instructMemLoc)); // Subtract value from accumulator
            std::cout << mainMemory->getAccumulator() << " which is now in the accumulator." << std::endl;
            break;
        case 32:
        case -32:
            DIVIDE(mainMemory, instructMemLoc); // Call DIVIDE function
            break;
        case 33:
        case -33:
            MULTIPLY(mainMemory, instructMemLoc); // Call MULTIPLY function
            break;
        case 40:
        case -40:
            mainMemory->setMemoryLocation(instructMemLoc); // Set new memory location for branching
            std::cout << "branching to " << mainMemory->getMemoryLocation() << "." << std::endl;
            branched = true; // Mark as branched
            break;
        case 41:
        case -41:
            if (mainMemory->getAccumulator() < 0) { // Check if accumulator is negative
                mainMemory->setMemoryLocation(instructMemLoc); // Branch to specified location
                std::cout << "Accumulator was negative branching to " << mainMemory->getMemoryLocation() << "." << std::endl;
                branched = true; // Mark as branched
            } else {
                std::cout << "Accumulator wasn't negative didn't branch." << std::endl; // No branching
            }
            break;
        case 42:
        case -42:
            if (mainMemory->getAccumulator() == 0) { // Check if accumulator is zero
                mainMemory->setMemoryLocation(instructMemLoc); // Branch to specified location
                std::cout << "Accumulator was zero branched to " << mainMemory->getMemoryLocation() << "." << std::endl;
                branched = true; // Mark as branched
            } else {
                std::cout << "Accumulator wasn't zero didn't branch." << std::endl; // No branching
            }
            break;
    }
    // If not branched, increment the memory location
    if (!(branched)) {
        mainMemory->setMemoryLocation(mainMemory->getMemoryLocation() + 1);
    }
}
