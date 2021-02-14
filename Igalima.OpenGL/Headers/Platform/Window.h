#pragma once

#include <string>
#include <iostream>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <OpenGL/GLWrapper.h>

struct WindowSettings
{
    uint32_t Width;
    uint32_t Height;
    std::string Title;
    void (*OnMouseMoved)(GLFWwindow*, double, double);
    void (*OnMouseScrolled)(GLFWwindow*, double, double);
    bool AutoInitialize;
};

class Window
{
public:
    Window(const WindowSettings& settings);
    Window(const Window&) = default;
    Window(Window&&) noexcept = default;
    ~Window();

public:
    Window& operator=(const Window&) = default;
    Window& operator=(Window&&) noexcept = default;

public:
    void Create();
    void Clear(const glm::vec4& color, const uint32_t& bufferBits);
    void SwapBuffers();
    void PollEvents();
    bool IsOpen();
    bool IsKeyPressed(const uint32_t& key);

public:
    glm::vec2 GetViewport() const;
    GLFWwindow* GetWindowHandle() const;

private:
    static void OnViewportResize(GLFWwindow* window, int width, int height);

private:
    WindowSettings m_Settings;
    GLFWwindow* m_Window = nullptr;
};