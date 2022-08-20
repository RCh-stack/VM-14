// Class Processor

#include "Memory.h"
#include "Registers.h"
#include "Command.h"

/*
struct command32
{
    uint16_t opcode : 8;
    uint16_t r1 : 4;
    uint16_t r2 : 4;
    uint16_t address : 16;
};
*/

class Processor
{
private:
    Memory *memory_;
    Registers *regs_;

public:
    Processor(Memory *memory, Registers *regs) : memory_(memory), regs_(regs){ }
    enum opcodes
    {
    stop = 0,
    iadd = 1,   isub = 2,   imul = 3,   idiv = 4,
    fadd = 5,   fsub = 6,   fmul = 7,   fdiv = 8,
    in = 9,     iout = 10,  fin = 11,   fout = 12,
    iand = 13,  ior = 14,   ixor = 15,  inot = 16,
    movrr = 17, movmr = 18, movrm = 19,
    jmp = 20,   jmpr = 21,  jmpi = 22,  je = 23, jl = 24, jg = 25,
    call = 26,  ret = 27
    };
    
    uint16_t get_command() { return command32.opcode; }
    uint16_t get_r1() { return command32.r1; }
    uint16_t get_r2() { return command32.r2; }
    uint16_t get_address() { return command32.address; }
    
    void load_command(const std::string fname); // -- load program --
    void reset_flags(Registers &regs); // -- reset flags --
    void start(std::string name); // -- run processor --
};

#pragma once
