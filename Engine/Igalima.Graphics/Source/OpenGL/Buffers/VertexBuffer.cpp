#include "OpenGL/Buffers/VertexBuffer.h"
#include "OpenGL/Wrapper.h"

namespace GL
{
    VertexBuffer::VertexBuffer(const u32& size, const DrawMode& drawMode)
        : m_DrawMode(drawMode)
    {
        Initialize(size, nullptr, drawMode);
    }

    VertexBuffer::VertexBuffer(const float* vertices, const u32& size, const DrawMode& drawMode)
        : m_DrawMode(drawMode)
    {
        Initialize(size, vertices, drawMode);
    }

    VertexBuffer::VertexBuffer(const std::vector<float>& vertices, const DrawMode& drawMode)
        : m_DrawMode(drawMode)
    {
        Initialize(static_cast<u32>(vertices.size() * sizeof(float)), vertices.data(), drawMode);
    }

    VertexBuffer::~VertexBuffer()
    {
        Delete();
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::Delete()
    {
        glDeleteBuffers(1, &m_Id);
    }

    const u32& VertexBuffer::GetId() const
    {
        return m_Id;
    }

    void VertexBuffer::Initialize(const u32& size, const void* vertices, const DrawMode& drawMode)
    {
        glGenBuffers(1, &m_Id);
        Bind();
        glBufferData(GL_ARRAY_BUFFER, size, vertices, static_cast<GLenum>(drawMode));
    }
}