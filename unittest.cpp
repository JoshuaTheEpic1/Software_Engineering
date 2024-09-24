#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "operations.h"
using namespace std;

istringstream input;
ostringstream output;

void workingLoadWord(){
    vector<int> mainMemory;
    int accumulator = 0;
    int *accumptr = &accumulator;
    int currMemLoc = 0;
    mainMemory.resize(3);
    mainMemory.at(0) = 10;
    mainMemory.at(1) = 20;
    mainMemory.at(2) = 30;
    loadWord(accumptr, &mainMemory, 1);
    if(*accumptr == 20){
        cout << "LoadWord test passed" << endl;
    }else{
        cout << "LoadWord test failed: Expected " << mainMemory.at(1) << " but got " << *accumptr << endl;
    }
}

void oobLoadWord(){
  vector<int> mainMemory;
  int accumulator = 0;
  int *accumptr = &accumulator;
  int currMemLoc = 0;
  mainMemory.resize(3);
  mainMemory.at(0) = 10;
  mainMemory.at(1) = 20;
  mainMemory.at(2) = 30;

  try {
    loadWord(accumptr, &mainMemory, 3); //out of bounds
    cout << "Out of bounds LoadWord test failed" << endl;
  } catch (std::out_of_range const &e) {
    cout << "Out of bounds LoadWord test passed" << endl;
  } catch (...) {
    cout << "Out of bounds LoadWord test failed: unexpected exception" << endl;
  }
}

void workingStoreWord(){
    vector<int> mainMemory;
    int accumulator = 0;
    int *accumptr = &accumulator;
    int currMemLoc = 0;
    mainMemory.resize(3);
    mainMemory.at(0) = 10;
    mainMemory.at(1) = 20;
    loadWord(accumptr, &mainMemory, 1);
    storeWord(accumptr, &mainMemory, 2);
    if(mainMemory.at(2) == 20){
        cout << "StoreWord test passed" << endl;
    }else{
        cout << "StoreWord test failed: Expected " << mainMemory.at(1) << " but got " << mainMemory.at(2) << endl;
    }
}

void oobStoreWord() {
    vector<int> mainMemory;
    int accumulator = 0;
    int *accumptr = &accumulator;
    int currMemLoc = 0;
    mainMemory.resize(3);
    mainMemory.at(0) = 10;
    mainMemory.at(1) = 20;
    mainMemory.at(2) = 30;

    try {
        storeWord(accumptr, &mainMemory, 4); //out of bounds
        cout << "Out of bounds StoreWord test failed: unexpected exception" << endl;
    } catch (std::out_of_range const &e) {
        cout << "Out of bounds StoreWord test passed" << endl;
    } catch (...) {
        cout << "Out of bounds StoreWord test failed: unexpected exception" << endl;
    }
}

void workingBranch(){ // tests both instruction +40/-40 for changing the current memory location to the correct location.
    vector<int> mainMemory;
    int accumulator = 0;
    int *accumptr = &accumulator;
    int currMemLoc = 0;
    mainMemory.resize(3);
    doInstruction("+40",&mainMemory,2,accumptr,&currMemLoc); 
    if(currMemLoc != 2){
        cout << "Branch test workingBranch: failed change to correct location, location is: " << currMemLoc << " should be 2." << endl;
    }
    else{
        doInstruction("-40",&mainMemory,1,accumptr,&currMemLoc);
        if(currMemLoc !=1){
            cout << "Branch test workingBranch: failed test 2 location is: " << currMemLoc << " should be 1." << endl;
        }
        else{
            cout << "Branch test workingBranch: Passed." << endl;
        }
    }
    

}

void workingBranchNegative(){ // tests both instruction +41/-41 for changing the current memory location if accumulator is negative.
    vector<int> mainMemory;
    int accumulator = -10;
    int *accumptr = &accumulator;
    int currMemLoc = 0;
    mainMemory.resize(3);
    doInstruction("+41",&mainMemory,2,accumptr,&currMemLoc);
    if(currMemLoc !=2 ){
        cout << "Branch test workingBranchNegative: failed change to correct location, location is: " << currMemLoc << " should be 2." << endl;
    }
    else{
        accumulator = 10;
        doInstruction("-41",&mainMemory,2,accumptr,&currMemLoc);
        if(currMemLoc !=3){
            cout << "Branch test workingBranchNegative: part 2, failed changed location when it shouldn't have, location is: " << currMemLoc << " should be 2." << endl;
        }
        else{
            cout << "Branch test WorkingBranchNegative: Passed." << endl;
        }
    }
}

void workingBranchZero(){ // both insruction +42/-42 for changing memory location if the accumulator is 0.
    vector<int> mainMemory;
    int accumulator = 0;
    int *accumptr = &accumulator;
    int currMemLoc = 0;
    mainMemory.resize(3);
    doInstruction("+42",&mainMemory,2,accumptr,&currMemLoc);
    if(currMemLoc !=2 ){
        cout << "Branch test workingBranchZero: failed change to correct location, location is: " << currMemLoc << " should be 2." << endl;
    }
    else{
        accumulator = 10;
        doInstruction("-42",&mainMemory,2,accumptr,&currMemLoc);
        if(currMemLoc !=3){
            cout << "Branch test workingBranchZero: part 2, failed changed location when it shouldn't have, location is: " << currMemLoc << " should be 2." << endl;
        }
        else{
            cout << "Branch test workingBranchZero: Passed." << endl;
        }
    }
}
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
} 
void testAdd(){
    vector<int> mainMemory;
    int accumulator = 10;
    int *accumptr = &accumulator;
    int currMemLoc = 0;
    mainMemory.resize(3);
    mainMemory.at(2) = 20;
    doInstruction("+30",&mainMemory,2,accumptr,&currMemLoc);
    if(accumulator == 30){
        cout << "First test add passed." << endl;
        doInstruction("-30",&mainMemory,2,accumptr,&currMemLoc);
        if(accumulator == 50){
            cout << "Second test add passed." << endl;
        }
        else{cout << "Second test add failed. Should be 50 got: " << accumulator << endl;}
    }
    else{cout << "First test add failed. Should be 30 got: " << accumulator << endl;}
}
void testSubtract(){
    vector<int> mainMemory;
    int accumulator = 10;
    int *accumptr = &accumulator;
    int currMemLoc = 0;
    mainMemory.resize(3);
    mainMemory.at(2) = 20;
    doInstruction("+31",&mainMemory,2,accumptr,&currMemLoc);
    if(accumulator == -10){
        cout << "First test subtract passed." << endl;
        doInstruction("-31",&mainMemory,2,accumptr,&currMemLoc);
        if(accumulator == -30){
            cout << "Second test subtract passed." << endl;
        }
        else{cout << "Second test subtract failed. Should be -10 got: " << accumulator << endl;}
    }
    else{cout << "First test subtract failed. Should be 0 got: " << accumulator << endl;}
}
/*void testMultiply(){
    vector<int> mainMemory;
    int accumulator = 10;
    int *accumptr = &accumulator;
    int currMemLoc = 0;
    mainMemory.resize(3);
    mainMemory.at(2) = 20;
        doInstruction("+33",&mainMemory,2,accumptr,&currMemLoc);
    if(accumulator == 200){
        cout << "First test multiply passed." << endl;
        doInstruction("-33",&mainMemory,2,accumptr,&currMemLoc);
        if(accumulator == 4000){
            cout << "Second test multiply passed." << endl;
        }
        else{cout << "Second test multiply failed. Should be 4000 got: " << accumulator << endl;}
    }
    else{cout << "First test multiply failed. Should be 200 got: " << accumulator << endl;}
}
void testDivide(){
    vector<int> mainMemory;
    int accumulator = 10;
    int *accumptr = &accumulator;
    int currMemLoc = 0;
    mainMemory.resize(3);
    mainMemory.at(2) = 20;
    doInstruction("+32",&mainMemory,2,accumptr,&currMemLoc);
    if(accumulator == 10){
        cout << "First test divide passed." << endl;
        doInstruction("-32",&mainMemory,2,accumptr,&currMemLoc);
        if(accumulator == 1){
            cout << "Second test divide passed." << endl;
        }
        else{cout << "Second test divide failed. Should be 0 got: " << accumulator << endl;}
    }
    else{cout << "First test divide failed. Should be 0 got: " << accumulator << endl;}
}
*/
int UNITTESTING(){
    workingLoadWord();
    oobLoadWord();
    workingStoreWord();
    oobLoadWord();
    workingBranch();
    workingBranchNegative();
    workingBranchZero();
    test_READ();
    test_WRITE();
    testAdd();
    testSubtract();
    testDivide();
    testMultiply();


    return 0;
}
