#include "Processor.h"

void Processor::reset_flags(Registers &regs)
{
    regs.psw.IP = 0;
    regs.psw.ZF = 0;
    regs.psw.CF = 0;
    regs.psw.SF = 0;
}

void Processor::load_command(const std::string name)
{
    command32 cmd; // -- command--
    Registers regs; // -- registers and flags --
    Memory mem; // -- memory --

    std::ifstream f(name);
    if(!f)
    {
        std::cout << "\nFile not found.\n" << std::endl;
        system("pause");
        exit(0);
    }
    uint16_t regis = 0; // -- download address --
    uint16_t str = 0; // -- lines read --
    for(std::string word; f >> word;)
    {
        if(word == "p")
        {
            regis = 0;
            f >> word;
            str++;
        } else
        if(word == "i")
        {
            f >> word;
            int32_t num = std::stoi(word);
            regs.grp.push_int(regis, num);
            regis++;
            str++;
        } else
        if(word == "u")
        {
            f >> word;
            uint32_t num = std::stoi(word);
            regs.grp.push_uint(regis, num);
            regis++;
            str++;
        } else
        if(word == "f")
        {
            f >> word;
            float num = std::stof(word);
            regs.grpf.push_float(regis, num);
            regis++;
            str++;
        } else
        if(word == "c")
        {
            f >> word;
            cmd.opcode = std::stoi(word);
            f >> word;
            cmd.r1 = std::stoi(word);
            f >> word;
            cmd.r2 = std::stoi(word);
            f >> word;
            cmd.address = std::stoi(word);
            if(cmd.opcode == 1 || cmd.opcode == 2 || cmd.opcode == 3 || cmd.opcode == 4)
            {
                IMath im;
                im(mem, regs, cmd);
            }
            if(cmd.opcode == 5 || cmd.opcode == 6 || cmd.opcode == 7 || cmd.opcode == 8)
            {
                FMath fm;
                fm(mem, regs, cmd);
            }
            if(cmd.opcode == 9 || cmd.opcode == 11)
            {
                Input in;
                in(mem, regs, cmd);
            }
            if(cmd.opcode == 10 || cmd.opcode == 12)
            {
                Output out;
                out(mem, regs, cmd);
            }
            if(cmd.opcode == 13 || cmd.opcode == 14 || cmd.opcode == 15 || cmd.opcode == 16)
            {
                Logic log;
                log(mem, regs, cmd);
            }
            if(cmd.opcode == 17 || cmd.opcode == 18 || cmd.opcode == 19)
            {
                Transition tr;
                tr(mem, regs, cmd);
            }
            if(cmd.opcode == 20 || cmd.opcode == 21 || cmd.opcode == 22 || cmd.opcode == 23 || cmd.opcode == 24 || cmd.opcode == 25 ||cmd.opcode == 26 || cmd.opcode == 27)
            {
                Jump jp;
                jp(mem, regs, cmd);
            }
            str++;
        } else
        if(word == "s") // -- if met prefix"s" --
        {
            std::cout << "\nThe processor is stopped, the program is terminated.\n" << std::endl;
            reset_flags(regs); // -- reset flags --
            str++;
            system("pause");
            exit(0); // -- exit from the program --
        }
    }
}

void Processor::start(std::string name)
{
    std::ifstream f(name);
    if(!f)
    {
        std::cout << "\nFile not found.\n" << std::endl;
        system("pause");
        exit(0);
    }
    else
        std::cout << "\nFile downloaded.\n" << std::endl;
    load_command(name); // -- command load call --
}
