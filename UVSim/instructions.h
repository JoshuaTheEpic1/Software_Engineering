#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include <vector>
#include <string>
#include <QString>



class Instructions
{
public:
    Instructions();
    void setInstruction(int location,QString value);
    void setinstructionMemoryLocation(int instructionMemoryLocation){this->instructionMemoryLocation = instructionMemoryLocation;};
    std::vector<QString> getFullInstructionTable() {return this->fullInstructionTable;}
    int getInstructMemoryLocation(){return this->instructionMemoryLocation;}
    bool fourDigitInput = false;
    bool sixDigitInput = false;
private:
    std::vector<QString> fullInstructionTable;
    int instructionMemoryLocation = 0;


};

#endif // INSTRUCTIONS_H
