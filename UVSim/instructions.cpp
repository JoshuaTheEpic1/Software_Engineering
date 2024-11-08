#include "instructions.h"
#include <QString>


Instructions::Instructions() {
    this->fullInstructionTable.resize(250);
    for(int i = 0; i<this->fullInstructionTable.size(); i++){
        this->fullInstructionTable.at(i) = " ";
    }
}


void Instructions::setInstruction(int location,QString value){
    this->fullInstructionTable.at(location) = value;

}
