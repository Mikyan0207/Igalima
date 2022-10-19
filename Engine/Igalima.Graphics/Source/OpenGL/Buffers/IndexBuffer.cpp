#include "OpenGL/Buffers/IndexBuffer.h"
#include "OpenGL/Wrapper.h"

namespace GL
{
    IndexBuffer::IndexBuffer(const u32* indices, const u32& size, const DrawMode& drawMode)
        : m_DrawMode(drawMode)
    {
        Initialize(size, indices, drawMode);
    }

    IndexBuffer::IndexBuffer(const std::vector<u32>& indices, const DrawMode& drawMode)
        : m_DrawMode(drawMode)
    {
        Initialize(static_cast<u32>(indices.size() * sizeof(u32)), indices.data(), drawMode);
    }

    IndexBuffer::~IndexBuffer()
    {
        Delete();
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
    }

    void IndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::Delete()
    {
        if (m_Id != 0)
        {
            glDeleteBuffers(1, &m_Id);
        }
    }

    const u32& IndexBuffer::GetId() const
    {
        return m_Id;
    }

    void IndexBuffer::Initialize(const u32& size, const u32* indices, const DrawMode& drawMode)
    {
        glGenBuffers(1, &m_Id);
        Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, static_cast<GLenum>(drawMode));
    }
}