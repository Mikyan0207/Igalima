#include <iostream>

#include <Common/Types.h>
#include <Common/Static.h>

#include <OS/Win32/Win32Window.h>
#include <Memory/StackAllocator.h>
#include <OpenGL/GLVertex.h>

int main()
{
    Win32::Window window("osu! clone", 1280, 720);
    
    GLVertex vertex {
        Math::Vector3f{10.0f, 1.0f, 0.0f},
        Math::Vector2f{5.0f, 5.0f},
        Math::Vector3f{1.0f, -1.0f, 0.0f}
    };
    
    return 0;
}