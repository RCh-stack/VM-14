// Interface of the Command class and command classes derived from it

struct command32
{
    uint16_t opcode : 8;
    uint16_t r1 : 4;
    uint16_t r2 : 4;
    uint16_t address : 16;
};

class Command
{
public:
    virtual void operator()(Memory &mem, Registers &regs, command32 &cmd);
};

class Input : public Command
{
public:
    void operator()(Memory &mem, Registers &regs, command32 &cmd);
};

class Output : public Command
{
public:
    void operator()(Memory &mem, Registers &regs, command32 &cmd);
};

class IMath : public Command
{
public:
    void operator()(Memory &mem, Registers &regs, command32 &cmd);
};

class FMath : public Command
{
public:
    void operator()(Memory &mem, Registers &regs, command32 &cmd);
};

class Compare : public Command
{
public:
    void operator()(Memory &mem, Registers &regs, command32 &cmd);
};

class IntegerCompare : public Compare
{
public:
    void operator()(Memory &mem, Registers &regs, command32 &cmd);
};

class RealCompare : public Compare
{
public:
    void operator()(Memory &mem, Registers &regs, command32 &cmd);
};

class Logic : public Command
{
public:
    void operator()(Memory &mem, Registers &regs, command32 &cmd);
};

class Transition : public Command
{
public:
    void operator()(Memory &mem, Registers &regs, command32 &cmd);
};

class Jump : public Command
{
public:
    void operator()(Memory &mem, Registers &regs, command32 &cmd);
};

#pragma once
