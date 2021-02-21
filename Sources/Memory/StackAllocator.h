#ifndef _STACK_ALLOCATOR_H
#define _STACK_ALLOCATOR_H

#include <cstring>

#include <Common/Types.h>
#include <Common/Igalima.h>

namespace Memory
{
    // NOTE(Mikyan): Make this class non-copiable?
    class IGALIMA_API StackAllocator
    {
        public:
        explicit StackAllocator(u32 sizeInBytes);
        StackAllocator(const StackAllocator&) = default;
        StackAllocator(StackAllocator&&) noexcept = default;
        ~StackAllocator();
        
        public:
        StackAllocator& operator=(StackAllocator&) = default;
        StackAllocator& operator=(StackAllocator&&) noexcept = default;
        
        public:
        void* Alloc(u32 size);
        void  Free(u32 marker);
        void  Clear();
        void  Delete();
        
        public:
        inline const u32& GetMarker() const { return m_Marker; };
        
        public:
        u8* m_Buffer;
        u32 m_BufferSize;
        
        // Stack cursor position.
        u32 m_Marker;
    };
};

#endif //_STACK_ALLOCATOR_H
