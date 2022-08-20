// -- Registers and flags --
#include <cinttypes>

class Registers
{
public:
    // -- flags --
    class PSW
    {
    public:
        uint16_t IP : 16; // -- program counter--
        uint16_t CF; // -- carry flag --
        uint16_t ZF; // -- null flag --
        uint16_t SF; // -- negative flag --

        PSW() : IP(0), CF(0), ZF(0), SF(0) { } // -- constructor --
        void reset_flags() noexcept { ZF = 0; CF = 0; SF = 0; } // -- reset flags --
    } psw{ };

    // -- integer registers --
    class GRP
	{
		int32_t grp[16] { };
    public:
        void push_int(uint16_t reg_number, int32_t num) { grp[reg_number] = num; }
        void push_uint(uint16_t reg_number, uint32_t num) { grp[reg_number] = num; }

        int32_t get_int(uint16_t reg_number) { return grp[reg_number]; }
        uint32_t get_uint(uint16_t reg_number) { return grp[reg_number]; }

	} grp{ };

	// -- float registers --
	class GRPF
	{
	    float grp[16] { };
    public:
        void push_float(uint16_t reg_number, float num) { grp[reg_number] = num; }
        float get_float(uint16_t reg_number) { return grp[reg_number]; }

	} grpf{ };
};

#pragma once
