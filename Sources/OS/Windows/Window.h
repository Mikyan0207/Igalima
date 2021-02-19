#ifndef _WIN32_H
#define _WIN32_H

#include <Windows.h>
#include <cassert>
#include <GL/gl.h>
#include <Common/Types.h>

// Platform dependent stuff.
namespace Win32
{
    struct Window
    {
        Window(const char* title, u32 width, u32 height);
        Window(const Window&) = delete;
        Window(Window&&) noexcept = delete;
        ~Window();
        
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) noexcept = delete;
        
        void Swap_Buffers();
        
        
        HWND Handle;
        HDC DeviceContext;
        HGLRC OpenGLContext;
        char* WindowClass;
    };
};

#endif //_WIN32_H
