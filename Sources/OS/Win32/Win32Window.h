#ifndef _WIN32_H
#define _WIN32_H

#include <Windows.h>
#include <cassert>
#include <GL/gl.h>
#include <Common/Types.h>

// Platform dependent stuff.
namespace Win32
{
    class __declspec(dllexport) Win32Window
    {
        public:
        Win32Window(const char* title, u32 width, u32 height);
        Win32Window(const Win32Window&) = delete;
        Win32Window(Win32Window&&) noexcept = delete;
        ~Win32Window();
        
        public:
        Win32Window& operator=(const Win32Window&) = delete;
        Win32Window& operator=(Win32Window&&) noexcept = delete;
        
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
