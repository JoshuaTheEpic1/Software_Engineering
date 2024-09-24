#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include "operations.h"

using namespace std;

void openFile(vector<string>* instruct, vector<int>* memLocations){
    ostringstream outstream;
    string line;
    string fileName;
    cout << "Plese type the file name, including file type, where the instructions are located. " << endl;
    cin >> fileName;
    //fileName = "Test3.txt"; // uncomment and comment above line for testing. so you don't have to type "Test3.txt everytime"
    ifstream file(fileName);
    while(!(file.is_open())){

        cout << "Invalid file name please reenter the name, including file type." << endl;
        cin >> fileName;
        cout << "file name is " << fileName << endl;
        ifstream temp(fileName);
        file.swap(temp);

    }
    cout << "file opened" << endl;
    while(getline(file, line)){
        outstream.str("");
        outstream << line[0] << line[1] << line[2];
        instruct->push_back(outstream.str());
        outstream.str("");
        outstream << line[3] << line[4];
        memLocations->push_back(stoi(outstream.str()));
    }
}   

//Can probably put these two into a separate file and link it here, but idk how
void READ(int instructMemLoc, vector<int>* mainMemory) {
    int tempword; //assumes all words are ints. Alteration is needed to store more dynamic data.
    cin >> tempword;
    if (instructMemLoc >= 0 && instructMemLoc < mainMemory->size()) { //checks if memory location is in bounds
        ///*
        if (!cin) { //Makes sure the inputted word is an int. We may need to change or remove if wanting to store non-int values
            cout << "error: invalid input. Expected an integer.\n";
        }
        //*/
        (*mainMemory)[instructMemLoc] = tempword;
    }
    else {
        cout << "error: memory location out of bounds.\n";
    }
}

void WRITE(int instructMemLoc, vector<int>* mainMemory) {
    if (instructMemLoc >= 0 && instructMemLoc < mainMemory->size()) { //checks if memory location is in bounds
        cout << (*mainMemory)[instructMemLoc];
    }
    else {
        cout << "error: memory location out of bounds.\n";
    }
}

void DIVIDE(vector<int>* mainMemory, int instructMemLoc, int* accumptr) {
    int divisor = mainMemory->at(instructMemLoc);
    cout << *accumptr << " / " << divisor << endl;
    if (divisor == 0) cout << "Divide by zero error" << endl;
    else *accumptr = *accumptr / divisor;
}

void MULTIPLY(vector<int>* mainMemory, int instructMemLoc, int* accumptr) {
    cout << *accumptr << " * " << mainMemory->at(instructMemLoc) << endl;
    *accumptr = *accumptr * mainMemory->at(instructMemLoc);
}

                                            // accumptr is a pointer to accumulator, use *accumptr to access accumulator
void doInstruction(string instruct,  vector<int>* mainMemory, int instructMemLoc, int* accumptr, int* currMemLoc){ // matches instruction to operation and calls the correct function
    bool branched = false; // prevents an extra count to current memory location if branched is true.
    if(instruct == ("+10") || instruct == ("-10") ){   // I wanted to use a switch but that doesn't work with strings (This is a tragedy -L)
        cout << "calling read function changing " <<  (*mainMemory).at(instructMemLoc) << endl;
        READ(instructMemLoc,mainMemory);
        cout << "called read changed to " << (*mainMemory).at(instructMemLoc) << endl;

    }
    else if(instruct == "+11" || instruct == "-11"){
        cout << "calling read function" << endl;
        WRITE(instructMemLoc,mainMemory);
    }
    else if(instruct == "+20" || instruct == "-20"){
        loadWord(accumptr, mainMemory, instructMemLoc);
        cout << *accumptr << " is now in accumulator" << endl;
    }
    else if(instruct == "+21" || instruct == "-21"){
        storeWord(accumptr, mainMemory, instructMemLoc);
        cout << "Value at memory location " << instructMemLoc << " is now " << mainMemory->at(instructMemLoc) << endl;
    }
    else if(instruct == "+30" || instruct == "-30"){
        cout << "*accumptr = ADD(accumptr, mainMemory->at(instructMemLoc))" << endl; // provides the pointer to the accumulator, and the int from mainMemory location from instruction
    }
    else if(instruct == "+31" || instruct == "-31"){
        cout << "*accumptr = SUBTRACT(accumptr, mainMemory->at(instructMemLoc))" << endl; // provides the pointer to the accumulator, and the int from mainMemory location from instruction
    }
    else if(instruct == "+32"  || instruct == "-32"){
        DIVIDE(mainMemory, instructMemLoc, accumptr);
    }
    else if(instruct == "+33" || instruct == "-33"){
        MULTIPLY(mainMemory, instructMemLoc, accumptr);
    }
    else if(instruct == "+40" || instruct == "-40"){
        *currMemLoc = instructMemLoc;
        cout << "branch changed to " << *currMemLoc << endl;
        branched = true;
    }
    else if(instruct == "+41" || instruct == "-41"){
        if(*accumptr < 0){
            *currMemLoc = instructMemLoc;
            cout << "BRANCHNEG: branch changed to " << *currMemLoc << endl;
            branched = true;
        }else{
             cout << "branchNEG: branch didn't change " << *currMemLoc << endl;
        }
    }
    else if(instruct == "+42" || instruct == "-42"){
        if(*accumptr == 0){
            *currMemLoc = instructMemLoc;
            cout << "branchZERO: branch changed to " << *currMemLoc << endl;
            branched = true;
        }else{
            cout << "branchZERO: didn't change " << *currMemLoc << endl;
        }   

        
    }
    else if(instruct == "+43" || instruct == "-43"){
        string userInput = "";
        cout << "Instructions pauses input anything to unpuase" << endl;
        while(userInput == ""){
            cin >> userInput;
        }
    }
    if(!(branched)){
        *currMemLoc++;
    }
}


int main(){
    vector<int> mainMemory;
    vector<string> instructions;
    vector<int> instructMemoryLocations;
    int currMemLoc = 0; // tracks location of what memory slot the program is at.
    int accumulator = 0;
    int *accumptr = &accumulator;
    mainMemory.resize(100); // Makes 100 memory slots.
    openFile(&instructions, &instructMemoryLocations); // asks for file name and populates the instructions memoryLocations vectors with each line
    for(int i = 0; i < instructions.size(); i++){
        doInstruction(instructions.at(i), &mainMemory, instructMemoryLocations.at(i), accumptr,  &currMemLoc);
        
    }

    /*Blank Space and call to run unit testing. Comment/Uncomment to test.
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "Unit Testing Results: " << endl;
    UNITTESTING();
    */
   
    return 0;
}
