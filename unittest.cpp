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

int UNITTESTING(){
    workingLoadWord();
    oobLoadWord();
    workingStoreWord();
    oobLoadWord();
    return 0;
}