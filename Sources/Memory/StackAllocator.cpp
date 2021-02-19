#include <Memory/StackAllocator.h>

namespace Memory
{
    StackAllocator::StackAllocator(u32 sizeInBytes)
    {
        // NOTE(Mikyan): We use char because it's exactly 1 byte.
        // We don't want to do some crazy template stuff.
        m_Buffer = new char[sizeInBytes]();
        m_BufferSize = sizeInBytes;
        m_Marker = sizeInBytes;
    }
    
    StackAllocator::~StackAllocator()
    {
    }
    
    void* StackAllocator::Alloc(u32 size)
    {
        // Update marker position.
        m_Marker -= size;
        
        // Meh.
        return(static_cast<char*>(m_Buffer) + m_Marker);
    }
    
    void StackAllocator::Free(u32 marker)
    {
        // NOTE(Mikyan): Not sure about this.
        if (m_BufferSize < m_Marker + marker)
            return;
        
        // Clear buffer.
        std::memset(static_cast<char*>(m_Buffer) + m_Marker, 0, marker);
        
        m_Marker += marker;
    }
    
    void StackAllocator::Clear()
    {
        // Clear Buffer.
        std::memset(static_cast<char*>(m_Buffer), 0, m_BufferSize);
        m_Marker = m_BufferSize;
    }
    
    void StackAllocator::Delete()
    {
        delete m_Buffer;
    }
};