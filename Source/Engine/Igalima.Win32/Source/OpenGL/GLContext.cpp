#include "OpenGL/GLContext.h"

namespace Win32
{
    /// <summary>
    ///     Creates and initializes a new OpenGL context using WGL for Windows.
    ///     The newly created context is also made current for further uses of OpenGL.
    /// </summary>
    /// <remarks>
    ///     This code is platform specific and only works on Windows.
    ///     WGL (Wiggle) is an API between OpenGL and the windowing system interface of Windows.
    /// </remarks>
    /// <param name="hdc">
    ///     A handle to a device context (DC) for the client area of a specified window or for the entire screen.
    /// </param>
    GLContext::GLContext(const HDC hdc) : m_OpenGLContext(wglCreateContext(hdc))
    {
        assert(m_OpenGLContext != nullptr);
        wglMakeCurrent(hdc, m_OpenGLContext);
    }

    /// <summary>
    ///     Delete and release the OpenGL context.
    /// </summary>
    GLContext::~GLContext()
    {
        if (m_OpenGLContext != nullptr)
        {
            wglDeleteContext(m_OpenGLContext);
        }
    }
}