#ifndef _WIN32_H
#define _WIN32_H

#include <Windows.h>
#include <cassert>
#include <iostream>
#include <OS/glad.h>
#include <GL/gl.h>
#include <Common/Types.h>
#include <Common/Igalima.h>

// Platform dependent stuff.
namespace Win32
{
    class IGALIMA_API Window
    {
        public:
        Window(const char* title, u32 width, u32 height);
        Window(const Window&) = delete;
        Window(Window&&) noexcept = delete;
        ~Window();
        
        public:
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) noexcept = delete;
        
        public:
        void Swap_Buffers();
        
        public:
        HWND Handle;
        HDC DeviceContext;
        HGLRC OpenGLContext;
        char* WindowClass;
    };
};

#endif //_WIN32_H
