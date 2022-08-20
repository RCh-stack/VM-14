// Class Memory

#include "Memory.h"

//------------------------------------------------------------------------------------------
Memory::Memory() // -- constructor --
{
    memory_= new uint16_t [5000];
}

//------------------------------------------------------------------------------------------
Memory::~Memory() // -- destructor --
{
    delete [] memory_;
}

//------------------------------------------------------------------------------------------
void Memory::push_memory(int32_t num, uint16_t adr) // -- push in memory --
{
    memory_[adr] = num;
}

//------------------------------------------------------------------------------------------
void Memory::push_memory(uint32_t num, uint16_t adr) // -- push in memory --
{
    memory_[adr] = num;
}

//------------------------------------------------------------------------------------------
void Memory::push_memory(float num, uint16_t adr) // -- push in memory --
{
    memory_[adr] = num;
}

//------------------------------------------------------------------------------------------
int32_t Memory::get_memory_int(uint16_t adr) // -- get from memory --
{
    int32_t num = (int32_t)memory_[adr];
    return num;
}

//------------------------------------------------------------------------------------------
uint32_t Memory::get_memory_uint(uint16_t adr) // -- get from memory --
{
    uint32_t num = (uint32_t)memory_[adr];
    return num;
}

//------------------------------------------------------------------------------------------
float Memory::get_memory_float(uint16_t adr) // -- get from memory --
{
    float num = (float)memory_[adr];
    return num;
}
