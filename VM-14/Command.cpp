#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cstring>
#include <string>
#include <stdlib.h>
#include "Memory.h"
#include "Command.h"
#include "Processor.h"

using namespace std;

//------------------------------------------------------------------------------------------
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

void IMath::operator()(Memory &mem, Registers &regs, command32 &cmd)
{
    auto opc = cmd.opcode;
    switch(opc)
    {
        case 1:
        {
            int32_t num = regs.grp.get_int(cmd.r1) + regs.grp.get_int(cmd.r2);
            mem.push_memory(num, cmd.address);
            break;
        }
        case 2:
        {
            int32_t num = regs.grp.get_int(cmd.r1) - regs.grp.get_int(cmd.r2);
            mem.push_memory(num, cmd.address);
            break;
        }
        case 3:
        {
            int32_t num = regs.grp.get_int(cmd.r1) * regs.grp.get_int(cmd.r2);
            mem.push_memory(num, cmd.address);
            break;
        }
        case 4:
        {
            int32_t num = regs.grp.get_int(cmd.r1) / regs.grp.get_int(cmd.r2);
            mem.push_memory(num, cmd.address);
            break;
        }
    }
}

void FMath::operator()(Memory &mem, Registers &regs, command32 &cmd)
{
    auto opc = cmd.opcode;
    switch(opc)
    {
        case 5:
        {
            float num = regs.grpf.get_float(cmd.r1) + regs.grpf.get_float(cmd.r2);
            mem.push_memory(num, cmd.address);

            cout << "Result = ";
            printf("%g", regs.grpf.get_float(cmd.r1) + regs.grpf.get_float(cmd.r2));
            cout << "\n";
            break;

        }
        case 6:
        {
            float num = regs.grpf.get_float(cmd.r1) - regs.grpf.get_float(cmd.r2);
            mem.push_memory(num, cmd.address);

            cout << "Result = ";
            printf("%g", regs.grpf.get_float(cmd.r1) - regs.grpf.get_float(cmd.r2));
            cout << "\n";
            break;

        }
        case 7:
        {
            float num = regs.grpf.get_float(cmd.r1) * regs.grpf.get_float(cmd.r2);
            mem.push_memory(num, cmd.address);

            cout << "Result = ";
            printf("%g", regs.grpf.get_float(cmd.r1) * regs.grpf.get_float(cmd.r2));
            cout << "\n";
            break;

        }
        case 8:
        {
            float num = regs.grpf.get_float(cmd.r1) / regs.grpf.get_float(cmd.r2);
            mem.push_memory(num, cmd.address);

            cout << "Result = ";
            printf("%g", regs.grpf.get_float(cmd.r1) / regs.grpf.get_float(cmd.r2));
            cout << "\n";
            break;

        }
    }
}

void Input::operator()(Memory &mem, Registers &regs, command32 &cmd)
{
    auto opc = cmd.opcode;
    switch(opc)
    {
        case 9:
        {
            int32_t num;
            cin >> num;
            regs.grp.push_int(cmd.r1, num);
            break;
        }
        case 11:
        {
            float num;
            cin >> num;
            regs.grpf.push_float(cmd.r1, num);
            break;
        }
    }
}

void Output::operator()(Memory &mem, Registers &regs, command32 &cmd)
{
    auto opc = cmd.opcode;
    switch(opc)
    {
        case 10:
        {
            cout << "Результат = " << mem.get_memory_int(cmd.address) << endl;
            break;
        }
        case 12:
        {
            //cout << "Результат = " << (float)mem.get_memory_float(cmd.address) << endl;
            break;
        }
    }
}

void Logic::operator()(Memory &mem, Registers &regs, command32 &cmd)
{
    auto opc = cmd.opcode;
    switch(opc)
    {
        case 13:
        {
            int32_t num = regs.grp.get_int(cmd.r1) & regs.grp.get_int(cmd.r2);
            mem.push_memory(num, cmd.address);
            break;
        }
        case 14:
        {
            int32_t num = regs.grp.get_int(cmd.r1) | regs.grp.get_int(cmd.r2);
            mem.push_memory(num, cmd.address);
            break;
        }
        case 15:
        {
            int32_t num = regs.grp.get_int(cmd.r1) ^ regs.grp.get_int(cmd.r2);
            mem.push_memory(num, cmd.address);
            break;
        }
        case 16:
        {
            int32_t num = !regs.grp.get_int(cmd.r1);
            mem.push_memory(num, cmd.address);
            break;
        }
    }
}

void IntegerCompare::operator()(Memory &mem, Registers &regs, command32 &cmd)
{
    if(regs.grp.get_int(cmd.r1) == regs.grp.get_int(cmd.r2))
    {
        regs.psw.ZF = 1;
        regs.psw.SF = 0;
        regs.psw.CF = 0;
    } else
    if(regs.grp.get_int(cmd.r1) < regs.grp.get_int(cmd.r2))
    {
        regs.psw.ZF = 0;
        regs.psw.SF = 1;
        regs.psw.CF = 1;
    }
    else
    {
        regs.psw.ZF = 0;
        regs.psw.SF = 0;
        regs.psw.CF = 0;
    }
}

void RealCompare::operator()(Memory &mem, Registers &regs, command32 &cmd)
{
    if(regs.grpf.get_float(cmd.r1) == regs.grpf.get_float(cmd.r2))
    {
        regs.psw.ZF = 1;
        regs.psw.SF = 0;
        regs.psw.CF = 0;
    } else
    if(regs.grpf.get_float(cmd.r1) < regs.grpf.get_float(cmd.r2))
    {
        regs.psw.ZF = 0;
        regs.psw.SF = 1;
        regs.psw.CF = 1;
    }
    else
    {
        regs.psw.ZF = 0;
        regs.psw.SF = 0;
        regs.psw.CF = 0;
    }
}

void Transition::operator()(Memory &mem, Registers &regs, command32 &cmd)
{
    auto opc = cmd.opcode;
    switch(opc)
    {
        case 17:
        {
            int32_t num = regs.grp.get_int(cmd.r1);
            num = regs.grp.get_int(cmd.r2);
            regs.grp.push_int(cmd.r1, num);
            mem.push_memory(num, cmd.address);
            break;
        }
        case 18:
        {
            int32_t num = mem.get_memory_int(cmd.r1);
            regs.grp.push_int(num, cmd.r2);
            mem.push_memory(num, cmd.address);
            break;
        }
        case 19:
        {
            mem.push_memory(regs.grp.get_int(cmd.r1), cmd.address);
            break;
        }
    }
}

void Jump::operator()(Memory &mem, Registers &regs, command32 &cmd)
{
    auto opc = cmd.opcode;
    switch(opc)
    {
        case 20:
        {
            regs.psw.IP = cmd.address;
            cmd.opcode = regs.psw.IP;
            if(cmd.opcode == 0 || cmd.opcode == 1 || cmd.opcode == 2 || cmd.opcode == 3)
            {
                IMath im;
                im(mem, regs, cmd);
            }
            if(cmd.opcode == 4 || cmd.opcode == 5 || cmd.opcode == 6 || cmd.opcode== 7)
            {
                FMath fm;
                fm(mem, regs, cmd);
            }
            break;
        }
        case 21:
        {
            regs.psw.IP = regs.psw.IP + cmd.address;
            cmd.opcode = regs.psw.IP;
            if(cmd.opcode == 0 || cmd.opcode == 1 || cmd.opcode == 2 || cmd.opcode == 3)
            {
                IMath im;
                im(mem, regs, cmd);
            }
            if(cmd.opcode == 4 || cmd.opcode == 5 || cmd.opcode == 6 || cmd.opcode== 7)
            {
                FMath fm;
                fm(mem, regs, cmd);
            }
            break;
        }
        case 22:
        {
            regs.psw.IP = regs.psw.IP + cmd.r1;
            cmd.opcode = regs.psw.IP;
            if(cmd.opcode == 0 || cmd.opcode == 1 || cmd.opcode == 2 || cmd.opcode == 3)
            {
                IMath im;
                im(mem, regs, cmd);
            }
            if(cmd.opcode == 4 || cmd.opcode == 5 || cmd.opcode == 6 || cmd.opcode== 7)
            {
                FMath fm;
                fm(mem, regs, cmd);
            }
            break;
        }
        case 23:
        {
            IntegerCompare ic;
            ic(mem, regs, cmd);
            if(regs.psw.ZF == 1)
            {
                regs.psw.IP = cmd.address;
                cmd.opcode = regs.psw.IP;
                if(cmd.opcode == 0 || cmd.opcode == 1 || cmd.opcode == 2 || cmd.opcode == 3)
                {
                    IMath im;
                    im(mem, regs, cmd);
                }
                if(cmd.opcode == 4 || cmd.opcode == 5 || cmd.opcode == 6 || cmd.opcode== 7)
                {
                    FMath fm;
                    fm(mem, regs, cmd);
                }
            }
            else
                break;
            break;
        }
        case 24:
        {
            IntegerCompare ic;
            ic(mem, regs, cmd);
            if(regs.psw.CF == 1 && regs.psw.SF == 1)
            {
                regs.psw.IP = regs.psw.IP + cmd.address;
                cmd.opcode = regs.psw.IP;
                if(cmd.opcode == 0 || cmd.opcode == 1 || cmd.opcode == 2 || cmd.opcode == 3)
                {
                    IMath im;
                    im(mem, regs, cmd);
                }
                if(cmd.opcode == 4 || cmd.opcode == 5 || cmd.opcode == 6 || cmd.opcode== 7)
                {
                    FMath fm;
                    fm(mem, regs, cmd);
                }
            }
            else
                break;
            break;
        }
        case 25:
        {
            IntegerCompare ic;
            ic(mem, regs, cmd);
            if(regs.psw.CF == 0 && regs.psw.ZF == 0 && regs.psw.SF == 0)
            {
                regs.psw.IP = regs.psw.IP + cmd.r1;
                cmd.opcode = regs.psw.IP;
                if(cmd.opcode == 0 || cmd.opcode == 1 || cmd.opcode == 2 || cmd.opcode == 3)
                {
                    IMath im;
                    im(mem, regs, cmd);
                }
                if(cmd.opcode == 4 || cmd.opcode == 5 || cmd.opcode == 6 || cmd.opcode== 7)
                {
                    FMath fm;
                    fm(mem, regs, cmd);
                }
            }
            else
                break;
            break;
        }
        case 26:
        {
            regs.grp.push_int(regs.grp.get_int(cmd.r1), cmd.r1);
            regs.psw.IP = cmd.address;
            cmd.opcode = regs.psw.IP;
            if(cmd.opcode == 0 || cmd.opcode == 1 || cmd.opcode == 2 || cmd.opcode == 3)
            {
                IMath im;
                im(mem, regs, cmd);
            }
            if(cmd.opcode == 4 || cmd.opcode == 5 || cmd.opcode == 6 || cmd.opcode== 7)
            {
                FMath fm;
                fm(mem, regs, cmd);
            }
            break;
        }
        case 27:
        {
            regs.grp.push_int(regs.psw.IP, cmd.r1);
            break;
        }
    }
}
