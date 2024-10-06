#include "mainwindow.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include "operations.h"
#include <QApplication>
using namespace std;

const bool UNITTESTINGBOOL = false;

/*void openFile(vector<string>* instruct, vector<int>* memLocations){ // old code used for prototype.
    ostringstream outstream;
    string line;
    string fileName;
    cout << "Plese type the file name, including file type, where the instructions are located. " << endl;
    //cin >> fileName;
    fileName = "Test3.txt"; // uncomment and comment above line for testing. so you don't have to type "Test3.txt everytime"
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
}*/



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.createLists();
    /*if(!(UNITTESTINGBOOL)){
        vector<int> mainMemory;
        vector<string> instructions;
        vector<int> instructMemoryLocations;
        int currMemLoc = 0; // tracks location of what memory slot the program is at.
        int accumulator = 0;
        int *accumptr = &accumulator;
        mainMemory.resize(100); // Makes 100 memory slots.
        //openFile(&instructions, &instructMemoryLocations); // asks for file name and populates the instructions memoryLocations vectors with each line
        for(int i = 0; i < instructions.size(); i++){
            doInstruction(instructions.at(i), &mainMemory, instructMemoryLocations.at(i), accumptr,  &currMemLoc);

        }
    }
    else{


        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "Unit Testing Results: " << endl;
        UNITTESTING();
    }*/
    return a.exec();

}
