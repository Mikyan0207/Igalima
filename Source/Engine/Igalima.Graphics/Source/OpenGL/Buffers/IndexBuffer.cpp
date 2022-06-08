#include "OpenGL/Buffers/IndexBuffer.h"
#include "OpenGL/Wrapper.h"

namespace GL
{
    IndexBuffer::IndexBuffer(const u32* indices, const u32& size, const DrawMode& drawMode)
        : m_DrawMode(drawMode)
    {
        Initialize(m_Type, size, indices, drawMode);
    }

    IndexBuffer::IndexBuffer(const std::vector<u32>& indices, const DrawMode& drawMode)
        : m_DrawMode(drawMode)
    {
        Initialize(m_Type, static_cast<u32>(indices.size() * sizeof(u32)), indices.data(), drawMode);
    }

    IndexBuffer::~IndexBuffer()
    {
        Delete();
    }

    void IndexBuffer::Bind() const
    {
        Wrapper::BindBuffer(m_Type, m_Id);
    }

    void IndexBuffer::Unbind() const
    {
        Wrapper::BindBuffer(m_Type, 0);
    }

    void IndexBuffer::Delete()
    {
        if (m_Id != 0)
        {
            Wrapper::DeleteBuffer(m_Id);
        }
    }

    const u32& IndexBuffer::GetId() const
    {
        return m_Id;
    }

    void IndexBuffer::Initialize(const BufferType& type, const u32& size, const u32* indices, const DrawMode& drawMode)
    {
        Wrapper::GenerateBuffer(m_Id);
        Bind();
        Wrapper::BufferData(type, size, indices, drawMode);
    }
}