#include <Memory/Memory.h>

Memory::Memory(const uint64_t& size)
{
    m_Size = size;
    
    // TODO: VirtualAlloc(). 
}

Memory::~Memory()
{
    if(!VirtualFree(0, m_Size, MEM_DECOMMIT|MEM_RELEASE))
    {
        // TODO: Error message: Invalid VirtualFree.
    }
}