#include "OpenGL/Buffers/VertexBuffer.h"
#include "OpenGL/Wrapper.h"

namespace GL
{
    VertexBuffer::VertexBuffer(const u32& size, const DrawMode& drawMode)
        : m_DrawMode(drawMode)
    {
        Initialize(m_Type, size, nullptr, drawMode);
    }

    VertexBuffer::VertexBuffer(const float* vertices, const u32& size, const DrawMode& drawMode)
        : m_DrawMode(drawMode)
    {
        Initialize(m_Type, size, vertices, drawMode);
    }

    VertexBuffer::VertexBuffer(const std::vector<float>& vertices, const DrawMode& drawMode)
        : m_DrawMode(drawMode)
    {
        Initialize(m_Type, static_cast<u32>(vertices.size() * sizeof(float)), vertices.data(), drawMode);
    }

    VertexBuffer::~VertexBuffer()
    {
        Delete();
    }

    void VertexBuffer::Bind() const
    {
        Wrapper::BindBuffer(BufferType::ArrayBuffer, m_Id);
    }

    void VertexBuffer::Unbind() const
    {
        Wrapper::BindBuffer(BufferType::ArrayBuffer, 0);
    }

    void VertexBuffer::Delete()
    {
        Wrapper::DeleteBuffer(m_Id);
    }

    const u32& VertexBuffer::GetId() const
    {
        return m_Id;
    }

    void VertexBuffer::Initialize(const BufferType& type, const u32& size, const void* vertices, const DrawMode& drawMode)
    {
        Wrapper::GenerateBuffer(m_Id);
        Bind();
        Wrapper::BufferData(type, size, vertices, drawMode);
    }
}