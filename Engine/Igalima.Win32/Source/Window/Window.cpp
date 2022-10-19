#include "Window/Window.h"

namespace Win32
{
    /// <summary>
    ///     An application-defined function that processes messages sent to a window.
    ///     The WNDPROC type defines a pointer to this callback function.
    /// </summary>
    /// <param name="hwnd">
    ///     A handle to the window.
    /// </param>
    /// <param name="message">
    ///     The message.
    /// </param>
    /// <param name="wparam">
    ///     Additional message information.
    ///     The contents of this parameter depend on the value of the message parameter.
    /// </param>
    /// <param name="lparam">
    ///     Additional message information.
    ///     The contents of this parameter depend on the value of the message parameter.
    /// </param>
    /// <returns>
    ///     The return value is the result of the message processing and depends on the message sent.
    /// </returns>
    LRESULT CALLBACK WindowProc(HWND hwnd, const UINT message, const WPARAM wparam, const LPARAM lparam)
    {
        return DefWindowProcA(hwnd, message, wparam, lparam);
    }

    /// <summary>
    ///     Creates and initializes a new window.
    ///     This constructor does not create or initialize any OpenGL/Vulkan related code.
    /// </summary>
    /// <param name="createInfo">
    ///     Information used to create the window.
    /// </param>
    void Window::Initialize(const Win32::WindowCreateInfo& createInfo)
    {
        WNDCLASSA windowClass = {};

        windowClass.style = CS_VREDRAW | CS_HREDRAW;
        windowClass.lpfnWndProc = WindowProc;
        windowClass.lpszClassName = "IgalimaWindowClass";
        windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);

        if (!RegisterClassA(&windowClass))
            return; // abort instead of return?

        RECT r = { 0, 0, static_cast<LONG>(createInfo.Width), static_cast<LONG>(createInfo.Height) };
        AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW | WS_VISIBLE, FALSE);

        auto* const window = CreateWindowExA(0,
            "IgalimaWindowClass",
            createInfo.Title,
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            r.right - r.left,
            r.bottom - r.top,
            nullptr,
            nullptr,
            nullptr,
            nullptr);

        // We could/should use UnregisterClassA before exiting.
        // But the OS will clean everything for us so we don't need to waste time on this
        if (window == nullptr)
            return; // abort instead of return?

        // WGL is an API between Windows windowing system and OpenGL
        // We use it for context creation with OpenGL.
        constexpr PIXELFORMATDESCRIPTOR pfd =
        {
            sizeof(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            PFD_TYPE_RGBA,
            32, // Color depth of the frame buffer
            0, 0, 0, 0, 0, 0,
            0,
            0,
            0,
            0, 0, 0, 0,
            24, // Number of bits for the depth buffer
            8, // Number of bits for the stencil buffer
            0, // Number of aux. buffers in the frame buffer
            PFD_MAIN_PLANE,
            0,
            0, 0, 0
        };

        const HDC hdc = GetDC(window);
        const int pixelFormat = ChoosePixelFormat(hdc, &pfd);
        SetPixelFormat(hdc, pixelFormat, &pfd);

        this->Handle = window;
        this->DeviceContext = hdc;
        this->WindowClass = "IgalimaWindowClass";
    }

    /// <summary>
    ///     Release and destroy the device context (DC).
    ///     Destroy and unregister the window.
    /// </summary>
    void Window::Destroy()
    {
        ReleaseDC(this->Handle, this->DeviceContext);
        DestroyWindow(this->Handle);
        UnregisterClass(reinterpret_cast<LPCSTR>(this->WindowClass.c_str()), nullptr);

        this->Handle = nullptr;
	}

	/// <summary>
	///     Manage inputs and events for the window.
	/// </summary>
	void Window::PollEvents()
	{
        MSG message = {};

		while (PeekMessageA(&message,  Handle, 0, 0, PM_REMOVE))
		{
            if (message.message == WM_QUIT || message.message == WM_CLOSE)
                m_IsOpen = false;

			TranslateMessage(&message);
            DispatchMessageA(&message);
		}
	}

	// Name is bad but SwapBuffers is already used by Windows API
    // and the compiler doesn't care if it's in a namespace or a class..
    void Window::Swap_Buffers() const
    {
        SwapBuffers(DeviceContext);
    }
}