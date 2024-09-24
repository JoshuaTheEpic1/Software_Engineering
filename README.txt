
Welcome to BasicML.

to program in BasicML, you will need to select an operation and a memory location.

Operation: The first two numbers will select what operation you would like to perform.  A complete list of operations will be given later.
  |
 \|/
 XX  XX
     /|\
      |
Memory Location:  The last two numbers will select the memory location you want to access.

Accumulator: There is an accumulator value that begins at 0 and holds the results of math operations.  

READ = 10 Read an input from the keyboard into the location defined by the second pair of numbers.
WRITE = 11 Write a word from a the location defined by the second pair of numbers from memory to the screen.

Load/store operations:
LOAD = 20 Load a word from a the location defined by the second pair of numbers in memory into the accumulator.
STORE = 21 Store a word from the accumulator into a the location defined by the second pair of numbers in memory.

Arithmetic operation:
ADD = 30 Add a word from a the location defined by the second pair of numbers in memory to the word in the accumulator (leave the result in the accumulator)
SUBTRACT = 31 Subtract a word from a the location defined by the second pair of numbers in memory from the word in the accumulator (leave the result in the accumulator)
DIVIDE = 32 Divide the word in the accumulator by a word from a the location defined by the second pair of numbers in memory (leave the result in the accumulator).
MULTIPLY = 33 multiply a word from a the location defined by the second pair of numbers in memory to the word in the accumulator (leave the result in the accumulator).

To store the results of an operation, run the STORE operation 21XX to save it to location XX 

Control operation:
BRANCH = 40 runs the code at a location defined by the second pair of numbers in memory
BRANCHNEG = 41 Branch to a the location defined by the second pair of numbers in memory if the accumulator is negative.
BRANCHZERO = 42 Branch to a the location defined by the second pair of numbers in memory if the accumulator is zero.
HALT = 43 Pause the program
