#ifndef _WINDOW_H
#define _WINDOW_H

#include <cstdint>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct WindowSettings
{
    const char* Title;
    uint32_t Width;
    uint32_t Height;
    bool FullScreen;
    uint32_t OpenGL_MajorVersion;
    uint32_t OpenGL_MinorVersion;
};

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
    
    public:
    void Create();
    void Delete();
    bool IsOpen();
    
    public:
    WindowSettings Settings;
    
    private:
    GLFWwindow* m_Window;
};

#endif //_WINDOW_H
