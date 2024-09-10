#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

void openFile(vector<string>* instruct, vector<int>* memLoc){
    ostringstream outstream;
    string line;
    string fileName;
    cout << "Plese type the file name, including file type, where the instructions are located. " << endl;
    cin >> fileName;
    //fileName = "Test1.txt"; // uncomment and comment above line for testing. so you don't have to type "Test1.txt everytime"
    ifstream file(fileName);
    while(!(file.is_open())){

        cout << "Invalid file name please reenter the name, including file type." << endl;
        cin >> fileName;
        cout << "file name is " + fileName << endl;
        ifstream temp(fileName);
        file.swap(temp);

    }
    cout << " file opened" << endl;
    while(getline(file, line)){
        outstream.str("");
        outstream << line[0] << line[1] << line[2];
        instruct->push_back(outstream.str());
        outstream.str("");
        outstream << line[3] << line[4];
        memLoc->push_back(stoi(outstream.str()));
    }
}
void doInstruction(string instruct, int memLoc, int* accumulator,vector<int>* memoryLocations, int* currMemLoc){ // matches instruction to operation and calls the correct function
    bool branched = false; // prevents an extra count to current memory location if branched is true.
    if(instruct == ("+10") || instruct == ("-10") ){   // I wanted to use a switch but that doesn't work with strings
        cout << "READ(&memoryLocations)" << endl;
    }
    else if(instruct == "+11" || instruct == "-11"){
        cout << "WRITE(memLoc, const &memoryLocations)" << endl;
    }
    else if(instruct == "+20" || instruct == "-20"){
        cout << "LOAD(&accumulator, const &memoryLocations)" << endl;
    }
    else if(instruct == "+21" || instruct == "-21"){
        cout << "STORE(&accumulator, &memoryLocations)" << endl;
    }
    else if(instruct == "+30" || instruct == "-30"){
        cout << "*accumulator = ADD(&accumulator, int memLoc, const &memoryLocations)" << endl;
    }
    else if(instruct == "+31" || instruct == "-31"){
        cout << "*accumulator = SUBTRACT(&accumulator,int memLoc,const &memoryLocations)" << endl;
    }
    else if(instruct == "+32"  || instruct == "-33"){
        cout << "*accumulator = DIVIDE(&accumulator,int memLoc,const &memoryLocations)" << endl;
    }
    else if(instruct == "+33" || instruct == "-33"){
        cout << "*accumulator = MULTIPLY(&accumulator,int memLoc, const &memoryLocations)" << endl;
    }
    else if(instruct == "+40" || instruct == "-40"){
        *currMemLoc = memLoc;
        cout << "branch changed to " << *currMemLoc << endl;
        branched = true;
    }
    else if(instruct == "+41" || instruct == "-41"){
        if(*accumulator < 0){
            *currMemLoc = memLoc;
            cout << "BRANCHNEG branch changed to " << *currMemLoc << endl;
        }else{
             cout << "branchNEG branch didn't change " << *currMemLoc << endl;
        }
        branched = true;
    }
    else if(instruct == "+42" || instruct == "-42"){
        if(*accumulator == 0){
            *currMemLoc = memLoc;
            cout << "branchZERO branch changed to " << *currMemLoc << endl;
        }else{
            cout << "branchZERO didn't change " << *currMemLoc << endl;
        }   
        branched = true;
        
    }
    else if(instruct == "+43" || instruct == "-43"){
        string userInput = "";
        cout << "Instructions pauses input anything to unpuase" << endl;
        while(userInput == ""){
            cin >> userInput;
        }
        branched = true;
    }
    if(!(branched)){
        *currMemLoc++;
        cout << "branching is false" << endl;
    }
}
int main(){
    vector<int> memory;
    vector<string> instructions;
    vector<int> memoryLocations;
    int currMemLoc = 0; // tracks location of what memory slot the program is at.
    int accumulator = 0;
    int *accumptr = &accumulator;
    memory.resize(100); // Makes 100 memory slots.
    openFile(&instructions, &memoryLocations); // asks for file name and populates the instructions vector with each line
    for(int i = 0; i < instructions.size(); i++){
        doInstruction(instructions.at(i), memoryLocations.at(i), accumptr, &memoryLocations, &currMemLoc);
        
    }

}