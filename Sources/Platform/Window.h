#ifndef _WINDOW_H
#define _WINDOW_H

#include <cstdint>

struct WindowSettings
{
    const char* Title;
    uint32_t Width;
    uint32_t Height;
    uint32_t OpenGL_MajorVersion;
    uint32_t OpenGL_MinorVersion;
}

class Window
{
    public:
    Window(WindowSettings settings);
    Window(const Window&) = delete;
    Window(Window&&) noexcept = delete;
    ~Window();
    
    public:
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&) noexcept = delete;
};

#endif //_WINDOW_H
