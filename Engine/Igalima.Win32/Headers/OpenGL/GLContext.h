#pragma once

#include <Windows.h>
#include <cassert>
#include <iostream>
#include <glad/glad.h>
#include <gl/GL.h>

#include "Igalima.Win32.h"

namespace Win32
{
    /// <summary>
    ///     The GLContext class wraps and simplify the creation and usage of a OpenGL context.
    /// </summary>
    /// <remarks>
    ///     <para>
    ///         A context stores all of the state associated with this instance of OpenGL.
    ///         When a context is destroyed, OpenGL is destroyed.
    ///     </para>
    ///     <para>
    ///         Contexts are localized within a particular process of execution on an operating system.
    ///         A process can create multiple OpenGL contexts.
    ///         Each context can represent a separate viewable surface, like a window in an application.
    ///     </para>
    ///     For more information see the OpenGL documentation.
    /// </remarks>
    class IGALIMA_WIN32_API GLContext
    {
    public:
        explicit GLContext(const HDC hdc);
        GLContext(const GLContext&) = delete;
        GLContext(GLContext&&) noexcept = delete;
        ~GLContext();

    public:
        GLContext& operator=(const GLContext&) = delete;
        GLContext& operator=(GLContext&&) noexcept = delete;

    private:
        HGLRC m_OpenGLContext;
    };
}