# Implementation Requirements
### Implement the virtual machine interpreter as a console application.
### Object-oriented approach.

> Processor - a separate class, divided into interface and implementation;

> Command execution - functor call (don't use switch operator!)

> Memory is a field in the class. Memory is a separate independent class; the memory itself is a dynamic array;

> Processor commands - hierarchy of functor classes; base class – abstract class Command with overloaded operator () operation

### Develop and describe in an explanatory note:
> command codes
  
> operand addressing methods
  
> set of flags-results
  
> command formats

> operand formats
  
### The following commands must be implemented:
> Upload/Download/Save

> Arithmetic (integer and fractional)

> Comparisons (integer and fractional)

> Bit operations

> Input-output (integer and fractional)

> Transitions (unconditional, conditional, to subroutine, return from subroutine)

### The program loader for the virtual machine is an independent function called in the main() function of the interpreter.

> The program code for the virtual machine must be written in a text file.

> The format for representing the program code in a file must be developed and described in an explanatory note.

> The loader must be able to load program code at any memory address

> The main program must take the file name as a command line argument, and pass it to the loader as a parameter when called.

# 14. Three-address, two operands in registers, one in memory

PSW = IP + Flags, 16 + 16 = 32 bits

Memory: 32-bit words, 16-bit address size

Data types:

Integer signed, unsigned - 4 bytes

Fractional - 4 bytes

RON - 16 pieces, 32 bits - whole

They are 32 bits - fractional

Command structure: 1 word

32 bits: COP - 8 bits, r1 - 4 bits, r2 - 4 bits, address (constant) - 16 bits

The result is in memory.

Register-to-register transfer

Transfer memory-register, register-memory

integer arithmetic

Fractional arithmetic

Transitions:

Unconditional:

> straight

> relative

> indirect direct

Conditional - the same, only with checking flags

To subroutine - return address in r1

Return from subroutine
