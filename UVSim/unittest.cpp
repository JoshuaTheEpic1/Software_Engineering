#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "operations.h"
using namespace std;

istringstream input;
ostringstream output;
bool unitTestPassed = true;
MainMemory UnitTestingMemory;
void workingLoadWord(){
    UnitTestingMemory.setAccumulator(0);
    UnitTestingMemory.setMemoryLocation(0);
    UnitTestingMemory.setValueAt(0,10);
    UnitTestingMemory.setValueAt(1,20);
    UnitTestingMemory.setValueAt(2,30);
    loadWord(&UnitTestingMemory,1);
    if(UnitTestingMemory.getAccumulator() == 20){
        cout << "LoadWord test passed" << endl;
    }else{
        cout << "LoadWord test failed: Expected " << UnitTestingMemory.getValueAt(1) << " but got " << UnitTestingMemory.getAccumulator() << endl;
        unitTestPassed = false;
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
        loadWord(&UnitTestingMemory,101); //out of bounds
        cout << "Out of bounds LoadWord test failed" << endl;
    } catch (std::out_of_range const &e) {
        cout << "Out of bounds LoadWord test passed" << endl;
    } catch (...) {
        cout << "Out of bounds LoadWord test failed: unexpected exception" << endl;
        unitTestPassed = false;
    }
}

void workingStoreWord(){
    UnitTestingMemory.setAccumulator(0);
    UnitTestingMemory.setMemoryLocation(0);
    UnitTestingMemory.setValueAt(0,10);
    UnitTestingMemory.setValueAt(1,20);
    loadWord(&UnitTestingMemory,1);
    storeWord(&UnitTestingMemory,2);
    if(UnitTestingMemory.getValueAt(2) == 20){
        cout << "StoreWord test passed" << endl;
    }else{
        cout << "StoreWord test failed: Expected " << UnitTestingMemory.getValueAt(1) << " but got " <<  UnitTestingMemory.getValueAt(1) << endl;
        unitTestPassed = false;
    }
}

void oobStoreWord() {
    UnitTestingMemory.setAccumulator(0);
    UnitTestingMemory.setMemoryLocation(0);
    UnitTestingMemory.setValueAt(0,10);
    UnitTestingMemory.setValueAt(1,20);


    try {
        storeWord(&UnitTestingMemory, 101); //out of bounds
        cout << "Out of bounds StoreWord test failed: unexpected exception" << endl;
    } catch (std::out_of_range const &e) {
        cout << "Out of bounds StoreWord test passed" << endl;
    } catch (...) {
        cout << "Out of bounds StoreWord test failed: unexpected exception" << endl;
        unitTestPassed = false;
    }
}

void workingBranch(){ // tests both instruction +40/-40 for changing the current memory location to the correct location.
    UnitTestingMemory.setAccumulator(0);
    UnitTestingMemory.setMemoryLocation(0);

    doInstruction(+40,2,&UnitTestingMemory);
    if(UnitTestingMemory.getMemoryLocation() != 2){
        cout << "Branch test workingBranch: failed change to correct location, location is: " << UnitTestingMemory.getMemoryLocation()<< " should be 2." << endl;
    }
    else{
        doInstruction(-40,1,&UnitTestingMemory);
        if(UnitTestingMemory.getMemoryLocation() !=1){
            cout << "Branch test workingBranch: failed test 2 location is: " << UnitTestingMemory.getMemoryLocation() << " should be 1." << endl;
            unitTestPassed = false;
        }
        else{
            cout << "Branch test workingBranch: Passed." << endl;
        }
    }


}

void workingBranchNegative(){ // tests both instruction +41/-41 for changing the current memory location if accumulator is negative.
    UnitTestingMemory.setAccumulator(-10);
    UnitTestingMemory.setMemoryLocation(0);
    doInstruction(+41,2,&UnitTestingMemory);
    if( UnitTestingMemory.getMemoryLocation() !=2 ){
        cout << "Branch test workingBranchNegative: failed change to correct location, location is: " << UnitTestingMemory.getMemoryLocation() << " should be 2." << endl;
        unitTestPassed = false;
    }
    else{
        UnitTestingMemory.setAccumulator(10);
        doInstruction(-41,2,&UnitTestingMemory);
        if(UnitTestingMemory.getMemoryLocation() !=3){
            cout << "Branch test workingBranchNegative: part 2, failed changed location when it shouldn't have, location is: " << UnitTestingMemory.getMemoryLocation() << " should be 2." << endl;
            unitTestPassed = false;
        }
        else{
            cout << "Branch test WorkingBranchNegative: Passed." << endl;
        }
    }
}

void workingBranchZero(){ // both insruction +42/-42 for changing memory location if the accumulator is 0.
    UnitTestingMemory.setAccumulator(0);
    UnitTestingMemory.setMemoryLocation(0);
    doInstruction(+42,2,&UnitTestingMemory);
    if(UnitTestingMemory.getMemoryLocation() !=2 ){
        cout << "Branch test workingBranchZero: failed change to correct location, location is: " << UnitTestingMemory.getMemoryLocation() << " should be 2." << endl;
        unitTestPassed = false;
    }
    else{
        UnitTestingMemory.setAccumulator(10);
        doInstruction(42,2,&UnitTestingMemory);
        if(UnitTestingMemory.getMemoryLocation() !=3){
            cout << "Branch test workingBranchZero: part 2, failed changed location when it shouldn't have, location is: " << UnitTestingMemory.getMemoryLocation() << " should be 2." << endl;
            unitTestPassed = false;
        }
        else{
            cout << "Branch test workingBranchZero: Passed." << endl;
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
void testAdd(){
    UnitTestingMemory.setAccumulator(10);
    UnitTestingMemory.setMemoryLocation(0);
    UnitTestingMemory.setValueAt(2,20);
    doInstruction(+30,2,&UnitTestingMemory);
    if(UnitTestingMemory.getAccumulator() == 30){
        cout << "First test add passed." << endl;
        doInstruction(-30,2,&UnitTestingMemory);
        if(UnitTestingMemory.getAccumulator() == 50){
            cout << "Second test add passed." << endl;
        }
        else{cout << "Second test add failed. Should be 50 got: " << UnitTestingMemory.getAccumulator() << endl; unitTestPassed = false;}
    }
    else{cout << "First test add failed. Should be 30 got: " << UnitTestingMemory.getAccumulator() << endl; unitTestPassed = false;}
}
void testSubtract(){
    UnitTestingMemory.setAccumulator(10);
    UnitTestingMemory.setMemoryLocation(0);
    UnitTestingMemory.setValueAt(2,20);
    doInstruction(+31,2,&UnitTestingMemory);
    if(UnitTestingMemory.getAccumulator() == -10){
        cout << "First test subtract passed." << endl;
        doInstruction(-31,2,&UnitTestingMemory);
        if(UnitTestingMemory.getAccumulator() == -30){
            cout << "Second test subtract passed." << endl;
        }
        else{cout << "Second test subtract failed. Should be -10 got: " << UnitTestingMemory.getAccumulator() << endl; unitTestPassed = false; }
    }
    else{cout << "First test subtract failed. Should be 0 got: " << UnitTestingMemory.getAccumulator() << endl; unitTestPassed = false;}
}
void divideTests(){
    UnitTestingMemory.setMemoryLocation(0);
    UnitTestingMemory.setValueAt(2,20);
    UnitTestingMemory.setValueAt(0,10);
    UnitTestingMemory.setValueAt(1,30);
    UnitTestingMemory.setValueAt(3,0);
    //Test 50 / 10
    UnitTestingMemory.setAccumulator(50);
    DIVIDE(&UnitTestingMemory,0);
    if (UnitTestingMemory.getAccumulator() == 5) cout << "Divide test 50 / 10: Passed" << endl;
    else cout << "Divide test 50 / 10: Failed" << endl;
    //Test divide by zero
    DIVIDE(&UnitTestingMemory,3);
    if (UnitTestingMemory.getAccumulator() == 5) cout << "Divide by zero test: Passed" << endl;
    else {cout << "Divide by zero test: Failed" << endl; unitTestPassed = false;} //
}

void multiplyTests(){
    UnitTestingMemory.setMemoryLocation(0);
    UnitTestingMemory.setValueAt(0,10);
    UnitTestingMemory.setValueAt(1,20);
    UnitTestingMemory.setValueAt(2,30);
    UnitTestingMemory.setValueAt(3,0);
    //Test 5 * 20
    UnitTestingMemory.setAccumulator(5);
    MULTIPLY(&UnitTestingMemory,1);
    if (UnitTestingMemory.getAccumulator()) cout << "Test 5 * 20: Passed" << endl;
    else {cout << "Test 5 * 20: Failed" << endl; unitTestPassed = false;}
    //Test 0 * 10
    UnitTestingMemory.setAccumulator(0);
    MULTIPLY(&UnitTestingMemory,0);
    if (UnitTestingMemory.getAccumulator() == 0) cout << "Test 0 * 10: Passed" << endl;
    else{ cout << "Test 0 * 10: Failed" << endl; unitTestPassed = false;}
}

int UNITTESTING(){
    workingLoadWord();
    oobLoadWord();
    workingStoreWord();
    oobLoadWord();
    workingBranch();
    workingBranchNegative();
    workingBranchZero();
    divideTests();
    multiplyTests();
    if(unitTestPassed == true){
        cout << "ALL TESTS PASS." << endl;
        return 1;
    }
    else{return 0;}

}
