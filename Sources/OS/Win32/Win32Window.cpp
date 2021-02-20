#include <OS/Win32/Win32Window.h>

// Windows Platform Layer

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    return DefWindowProc(hwnd, message, wparam, lparam);
}

namespace Win32
{
    Window::Window(const char* title, u32 width, u32 height)
    {
        WNDCLASSA windowClass = {};
        
        windowClass.style = CS_VREDRAW | CS_HREDRAW;
        windowClass.lpfnWndProc = WindowProc;
        windowClass.lpszClassName = "IgalimaWindowClass";
        windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
        
        if (!RegisterClassA(&windowClass))
            return; // abort instead of return?
        
        RECT r = {0, 0, static_cast<LONG>(width), static_cast<LONG>(height)};
        AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW | WS_VISIBLE, FALSE);
        
        auto* const window = CreateWindowExA(0,
                                             "IgalimaWindowClass",
                                             title,
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
        // And just with 5 lines of code we don't need GLFW anymore.
        PIXELFORMATDESCRIPTOR pfd = 
        {
            sizeof(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            PFD_TYPE_RGBA,
            32,                 // Colordepth of the framebuffer
            0, 0, 0, 0, 0, 0,
            0,
            0,
            0,
            0, 0, 0, 0,
            24,                 // Number of bits for the depth buffer
            8,                  // Number of bits for the stencil buffer
            0,                  // Number of aux buffers in the framebuffer
            PFD_MAIN_PLANE,
            0,
            0, 0, 0
        };
        
        // The latest available version of OpenGL on this machine should be
        // automaticaly used.
        HDC hdc = GetDC(window);
        int pixelFormat = ChoosePixelFormat(hdc, &pfd);
        SetPixelFormat(hdc, pixelFormat, &pfd);
        HGLRC context = wglCreateContext(hdc);
        
        // NOTE(Mikyan): Maybe we want to leave this assert even on release build
        // since we cannot run our game without a context.
        assert(context != nullptr);
        
        wglMakeCurrent(hdc, context);
        
        this->Handle = window;
        this->DeviceContext = hdc;
        this->OpenGLContext = context;
        this->WindowClass = "IgalimaWindowClass";
    }
    
    Window::~Window()
    {
        wglDeleteContext(this->OpenGLContext);
        
        ReleaseDC(this->Handle, this->DeviceContext);
        DestroyWindow(this->Handle);
        UnregisterClass(this->WindowClass, nullptr);
    }
    
    // Name is bad but SwapBuffers is already used by Windows API
    // and the compiler doesn't care if it's in a namespace or a class..
    void Window::Swap_Buffers()
    {
        SwapBuffers(DeviceContext);
    }
};