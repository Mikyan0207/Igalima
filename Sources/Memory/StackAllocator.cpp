#include <Memory/StackAllocator.h>

namespace Memory
{
    StackAllocator::StackAllocator(u32 sizeInBytes)
    {
        // u8 = 1 byte.
        // We don't want to do some crazy template stuff.
        m_Buffer = new u8[sizeInBytes]();
        m_BufferSize = sizeInBytes;
        m_Marker = sizeInBytes;
    }
    
    StackAllocator::~StackAllocator()
    {
        // This allocator is not scoped so we don't delete our buffer here.
        // We must call Delete() if we want to free the memory.
    }
    
    void* StackAllocator::Alloc(u32 size)
    {
        // Update marker position.
        m_Marker -= size;
        
        return(m_Buffer + m_Marker);
    }
    
    void StackAllocator::Free(u32 marker)
    {
        // NOTE(Mikyan): Not sure about this.
        if (m_BufferSize < m_Marker + marker)
            return;
        
        // Clear buffer.
        std::memset(m_Buffer + m_Marker, 0, marker);
        
        m_Marker += marker;
    }
    
    void StackAllocator::Clear()
    {
        // Clear Buffer.
        std::memset(m_Buffer, 0, m_BufferSize);
        m_Marker = m_BufferSize;
    }
    
    void StackAllocator::Delete()
    {
        delete m_Buffer;
    }
};