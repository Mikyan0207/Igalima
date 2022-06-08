#include "OpenGL/Wrapper.h"

namespace GL
{
    void Wrapper::GenerateBuffer(u32& id)
    {
        glGenBuffers(1, &id);
    }

    void Wrapper::DeleteBuffer(u32& id)
    {
        glDeleteBuffers(1, &id);
    }

    void Wrapper::BindBuffer(const BufferType& type, const u32& id)
    {
        glBindBuffer(static_cast<GLenum>(type), id);
    }

    void Wrapper::BufferData(const BufferType& type, const u32& size, const void* vertices, const DrawMode& drawMode)
    {
        glBufferData(static_cast<GLenum>(type), size, vertices, static_cast<GLenum>(drawMode));
    }
}