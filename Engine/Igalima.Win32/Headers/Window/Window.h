#pragma once

#include <Windows.h>
#include <string>
#include "Igalima.Win32.h"
#include "Window/WindowCreateInfo.h"

namespace Win32
{
    class IGALIMA_WIN32_API Window
    {
    public:
        Window() = default;
        Window(const Window&) = delete;
        Window(Window&&) noexcept = delete;
        ~Window() = default;

    public:
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) noexcept = delete;

    public:
        void Initialize(const WindowCreateInfo& createInfo);
        void Destroy();
        void PollEvents();

    public:
        [[nodiscard]] bool IsOpen() const { return m_IsOpen; }
        void Swap_Buffers() const;

    public:
        HWND Handle = nullptr;
        HDC DeviceContext = nullptr;
        std::string WindowClass;

    private:
        bool m_IsOpen = true;
    };
}