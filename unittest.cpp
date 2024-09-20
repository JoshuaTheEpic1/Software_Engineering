#include <iostream>
#include <vector>
#include "operations.h"

using namespace std;

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
        if(currMemLoc !=2){
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
        if(currMemLoc !=2){
            cout << "Branch test workingBranchZero: part 2, failed changed location when it shouldn't have, location is: " << currMemLoc << " should be 2." << endl;
        }
        else{
            cout << "Branch test workingBranchZero: Passed." << endl;
        }
    }
}
int UNITTESTING(){
    workingLoadWord();
    oobLoadWord();
    workingStoreWord();
    oobLoadWord();
    workingBranch();
    workingBranchNegative();
    workingBranchZero();
    return 0;
}