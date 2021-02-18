#include <OS/Win32.h>
#include <gl/gl.h>
#include <cassert>

// Windows Platform Layer

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    LRESULT result = 0;
    
    switch (message)
    {
        case WM_CREATE:
        {
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
            
            // The latest avaible version of OpenGL on this machine should be
            // automaticaly used.
            HDC hdc = GetDC(hwnd);
            int pixelFormat = ChoosePixelFormat(hdc, &pfd);
            SetPixelFormat(hdc, pixelFormat, &pfd);
            HGLRC context = wglCreateContext(hdc);
            
            // NOTE(Mikyan): Maybe we want to leave this assert even on release build
            // since we cannot run our game without a context.
            assert(context != nullptr);
            
            wglMakeCurrent(hdc, context);
            
            // We can release the DC I think?
            ReleaseDC(hwnd, hdc);
        } break;
        default:
        {
            result = DefWindowProc(hwnd, message, wparam, lparam);
        } break;
    }
    
    return(result);
}

int APIENTRY WinMain(HINSTANCE instance, HINSTANCE /*prevInstance*/, LPSTR, int)
{
    WNDCLASSA windowClass = {};
    
    windowClass.style = CS_VREDRAW | CS_HREDRAW;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = instance;
    windowClass.lpszClassName = "IgalimaWindowClass";
    
    if (!RegisterClassA(&windowClass))
        return -1;
    
    auto* const window = CreateWindowExA(0,
                                         "IgalimaWindowClass",
                                         "Igalima",
                                         WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                         CW_USEDEFAULT,
                                         CW_USEDEFAULT,
                                         CW_USEDEFAULT,
                                         CW_USEDEFAULT,
                                         nullptr,
                                         nullptr,
                                         instance,
                                         nullptr);
    
    if (window == nullptr)
        return -1;
    
    return 0;
}