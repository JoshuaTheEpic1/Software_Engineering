#ifndef MAINMEMORY_H
#define MAINMEMORY_H
#include <vector>

class MainMemory{
    public:
        MainMemory(); // default constructor makes 100 size vector
        MainMemory(int size); // if size is provided the vector is intialized to that size
        int getValueAt(int location){return mainMemory.at(location);}; // returns the value at a specfic memory location
        void setValueAt(int location, int value){this->mainMemory.at(location) = value;}; // sets the value at a specfic memory locatoin
        int getMemoryLocation(){return this->currMemLoc;}
        void setMemoryLocation(int newLocation){this->currMemLoc = newLocation;}
        int getAccumulator(){return this->accumulator;}
        void setAccumulator(int value){this->accumulator = value;}
        std::vector<int> getMemoryList(){return this->mainMemory;} // returns the entire vector
        void setAll(std::vector<int> memory, int currMemLoc, int accumulator);


    private:
        std::vector<int> mainMemory;
        int currMemLoc = 0; // tracks location of what memory slot the program is at.
        int accumulator = 0;


};

#endif // MAINMEMORY_H
