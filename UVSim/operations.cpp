#include <iostream>
#include <vector>
#include "operations.h"
#include <fstream>
#include <sstream>
#include "mainMemory.h"

const bool UNITTESTINGBOOL = false; // switch this to true if you want to unit test.

// assign accumulator value to that of the given memory location
void loadWord( MainMemory* mainMemory, int instructMemLoc){
    mainMemory->setAccumulator(mainMemory->getValueAt(instructMemLoc));
}

// store accumulator value into a given memory location
void storeWord(MainMemory* mainMemory, int instructMemLoc){
    mainMemory->setValueAt(instructMemLoc,mainMemory->getAccumulator());
}

void READ(int instructMemLoc, MainMemory* mainMemory, int value) {
    int tempword; //assumes all words are ints. Alteration is needed to store more dynamic data.
    if(UNITTESTINGBOOL){
        istringstream testInput;
        testInput.str("42");
        testInput >> tempword;
    }else{
        /* Currently un-needed with the input from GUI
        cout << "Enter the number you'd to store in memory." << endl;
        cin >> tempword;
        */
    }



    if (instructMemLoc >= 0 && instructMemLoc < mainMemory->getMemoryList().size()) { //checks if memory location is in bounds
        /*
        if (!cin) { //Makes sure the inputted word is an int. We may need to change or remove if wanting to store non-int values
            cout << "error: invalid input. Expected an integer.\n";
        }
        */
        mainMemory->setValueAt(instructMemLoc,value);}
    else {
        std::cout << "error: memory location out of bounds.\n";
    }
}

int WRITE(int instructMemLoc,  MainMemory* mainMemory) {
    if (instructMemLoc >= 0 && instructMemLoc < mainMemory->getMemoryList().size()) { //checks if memory location is in bounds
        cout << "Memory location: " << instructMemLoc << " has: " << mainMemory->getValueAt(instructMemLoc) << " saved." << endl;
        return mainMemory->getValueAt(instructMemLoc);
    }
    else {
        cout << "error: memory location out of bounds.\n";
    }
    return -1;
}

void DIVIDE(MainMemory* mainMemory, int instructMemLoc) {
    int divisor = mainMemory->getValueAt(instructMemLoc);
    cout << mainMemory->getAccumulator() << " / " << divisor << endl;
    if (divisor == 0) cout << "Divide by zero error" << endl;
    else mainMemory->setAccumulator(mainMemory->getAccumulator() / divisor);
}

void MULTIPLY(MainMemory* mainMemory, int instructMemLoc) {
    cout << mainMemory->getAccumulator() << " * " << mainMemory->getValueAt(instructMemLoc) << endl;
    mainMemory->setAccumulator(mainMemory->getAccumulator() * mainMemory->getValueAt(instructMemLoc));
}


void doInstruction(int instruct, int instructMemLoc, MainMemory* mainMemory){ // matches instruction to operation and calls the correct function
    bool branched = false; // prevents an extra count to current memory location if branched is true.
    switch(instruct){
        case 10:
        case -10:
            READ(instructMemLoc,mainMemory,10);
            cout << "Memory location: " << instructMemLoc << " has loaded: " << mainMemory->getValueAt(instructMemLoc) << "." << endl;
            break;
        case 11:
        case -11:
            WRITE(instructMemLoc,mainMemory);
            break;
        case 20:
        case -20:
            loadWord(mainMemory, instructMemLoc);
            cout << mainMemory->getAccumulator() << " is now in accumulator." << endl;
            break;
        case 21:
        case -21:
            storeWord(mainMemory, instructMemLoc);
            cout << "Value at memory location " << instructMemLoc << " is now " << mainMemory->getValueAt(instructMemLoc) << "." << endl;
            break;
        case 30:
        case -30:
            cout << "Adding: " << mainMemory->getAccumulator() << " + " << mainMemory->getValueAt(instructMemLoc) << " = ";
            mainMemory->setAccumulator(mainMemory->getAccumulator() + mainMemory->getValueAt(instructMemLoc));
            cout << mainMemory->getAccumulator() << " which is now in the accumulator."<< endl;
            break;
        case 31:
        case -31:
            cout << "Subtracting: " << mainMemory->getAccumulator() << " - " << mainMemory->getValueAt(instructMemLoc) << " = ";
            mainMemory->setAccumulator(mainMemory->getAccumulator() - mainMemory->getValueAt(instructMemLoc));
            cout << mainMemory->getAccumulator() << " which is now in the accumulator."<< endl;
            break;
        case 32:
        case -32:
            DIVIDE(mainMemory, instructMemLoc);
            break;
        case 33:
        case -33:
            MULTIPLY(mainMemory, instructMemLoc);
            break;
        case 40:
        case -40:
            mainMemory->setMemoryLocation(instructMemLoc);
            cout << "branching to " << mainMemory->getMemoryLocation() << "." << endl;
            branched = true;
            break;
        case 41:
        case -41:
            if(mainMemory->getAccumulator() < 0){
                mainMemory->setMemoryLocation(instructMemLoc);
                cout << "Accumulator was negative branching to " << mainMemory->getMemoryLocation() << "." << endl;
                branched = true;
            }else{
                cout << "Accumulator wasn't negative didn't branch." << endl;

            }
            break;
        case 42:
        case -42:
            if(mainMemory->getAccumulator() == 0){
                mainMemory->setMemoryLocation(instructMemLoc);
                cout << "Accumulator was zero branched to " << mainMemory->getMemoryLocation() <<  "." << endl;
                branched = true;
            }else{
                cout << "Accumulator wasn't zero didn't branch."<< endl;

            }

            break;


    }
    if(!(branched)){
        mainMemory->setMemoryLocation(mainMemory->getMemoryLocation()+1);
    }
}
