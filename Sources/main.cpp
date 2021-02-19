#include <iostream>

#include <Common/Types.h>
#include <Common/Static.h>

#include <OS/Win32Window.h>
#include <Memory/StackAllocator.h>


int main()
{
    // StackAllocator is not scoped!
    // We must call Delete() when we are done with it.
    Memory::StackAllocator sa(100);
    
    sa.Delete();
    
    return 0;
}