/* date = February 14th 2021 2:28 pm */

#ifndef _MEMORY_H
#define _MEMORY_H

#include <Windows.h>
#include <cstdint>

class Memory
{
    public:
    Memory(const uint64_t& size);
    Memory(const Memory&) = default;
    Memory(Memory&&) noexcept = default;
    ~Memory();
    
    public:
    Memory& operator=(const Memory&) = delete;
    Memory& operator=(Memory&&) noexcept = delete;
    
    private:
    uint64_t m_Size;
    void* m_Buffer;
}

#endif //_MEMORY_H
