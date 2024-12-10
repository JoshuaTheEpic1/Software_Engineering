
## Summary
UVSim is a basic virtual machine designed to aid students in the learning of machine language and computer architecture. Working off of the language BasicML, the program utilizes its accumulator, main memory, and register to perform various instructions.

Table of Contents
=================
* [BasicML Explained](#welcome-to-basicml)<br>
* [Example Operations](#examples-of-operations)<br>
* [Using The GUI](#using-the-gui) <br>
* [Install Instructions](#install-instructions)<br>


## Welcome to BasicML.
To program in BasicML, you will need to select an operation and a memory location.

<pre>
For 4 Digit Words:
 
Operation: The first two numbers will select what operation you would like to perform.
 |         A complete list of operations will be given later.
\|/
XX  YY
    /|\
     |
    Memory Location:  The last two numbers will select the memory location you want to access.
</pre>
<pre>
For 6 Digit Words:
 
Operation: The latter two of the first three numbers will select what operation you would like to perform.
 |         A complete list of operations will be given later.
\|/
XXX  YYY
    /|\
     |
    Memory Location:  The last three numbers will select the memory location you want to access.
</pre>

Accumulator: There is an accumulator with a value that begins at 0 and holds the results of math operations.  

Word: this is a line of BasicML code.  it consists of an operation, and a memory location, such as 30 (Add) and 43 (memory location 43) or a number up to 4 decimal places, positive or negative.

## Examples of Operations 
### Read/Write Operations

READ = 10 Read an input from the keyboard into the location defined by the second pair of numbers.

WRITE = 11 Write a word from the location defined by the second pair of numbers from memory to the screen.

===== EXAMPLES ===== <br>
READ 1015:  The user enters a value on their keyboard, which is saved in location 15.

WRITE 1120: The program displays the value stored at location 20.


### Load/Store Operations:

LOAD = 20 Load a word from the location defined by the second pair of numbers in memory into the accumulator.

STORE = 21 Store a word from the accumulator into the location defined by the second pair of numbers in memory.

===== EXAMPLES =====<br>
LOAD 2015:  The program takes a word at line 15 and places it in the accumulator

STORE 1120: The program stores the word currently in its accumulator and places it in memory location 20.

### Arithmetic Operations
ADD = 30 Add a word from  the location defined by the second pair of numbers in memory to the word in the accumulator (leave the result in the accumulator)

SUBTRACT = 31 Subtract a word from the location defined by the second pair of numbers in memory from the word in the accumulator (leave the result in the accumulator)

DIVIDE = 32 Divide the word in the accumulator by a word from the location defined by the second pair of numbers in memory (leave the result in the accumulator).

MULTIPLY = 33 Multiply a word from the location defined by the second pair of numbers in memory to the word in the accumulator (leave the result in the accumulator).

===== EXAMPLE =====<br>
NOTE: All results will be stored in the accumulator.

ADD = 3053 adds the value in the accumulator to the value at 53.  

SUBTRACT = 3123 subtracts the value in the accumulator from the value at 23. 

DIVIDE = 3253 divides the value in the accumulator by the value at 53. 

MULTIPLY = 3345 multiplies the value in the accumulator with the value at 45. 

To store the results of an operation, run the STORE operation 21XX to save it to location XX 

### Control Operations
BRANCH = 40 runs the word at a location defined by the second pair of numbers in memory

BRANCHNEG = 41 Branch to the location defined by the second pair of numbers in memory if the accumulator is negative.

BRANCHZERO = 42 Branch to the location defined by the second pair of numbers in memory if the accumulator is zero.

HALT = 43 Pause the program

===== EXAMPLE =====<br>

BRANCH = 4087 runs the word at location 87

BRANCHNEG = 4192 Branch to memory location 92 if the accumulator is negative.

BRANCHZERO = 4252 Branch to memory location 52 if the accumulator is zero.

HALT = 43XX Pauses the program.  The memory location does not change anything.

## Using the GUI
<img src="https://i.imgur.com/rg4QV5v.png" width="800" height="632"/><br>

## Install Instructions
This program requires C++ to run.<br>
You can download the most recent release [here](https://github.com/JoshuaTheEpic1/Software_Engineering/releases).<br> 
You can alternatively build UVSim using the Qt program, which you can grab [here](https://www.qt.io/download-dev).
