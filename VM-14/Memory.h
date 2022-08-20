// Class Memory

#include <iostream>
#include <string>
#include <fstream>
#include <cinttypes>

class Memory
{
private:
	uint16_t *memory_;

public:
    Memory(); // -- constructor --
    ~Memory(); // -- destructor--

	// -- push in memory --
    void push_memory(int32_t num, uint16_t adr);
    void push_memory(uint32_t num, uint16_t adr);
    void push_memory(float num, uint16_t adr);

    // -- get from memory --
    int32_t get_memory_int(uint16_t adr);
    uint32_t get_memory_uint(uint16_t adr);
    float get_memory_float(uint16_t adr);
};

#pragma once
