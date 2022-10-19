#include "OpenGL/Buffers/VertexArray.h"
#include "OpenGL/Wrapper.h"
#include <algorithm>

namespace GL
{
    VertexArray::VertexArray()
    {
        Initialize();
    }

    VertexArray::~VertexArray()
    {
        Delete();
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(m_Id);
    }

    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void VertexArray::Delete()
    {
        if (m_Id != 0)
        {
            glDeleteVertexArrays(1, &m_Id);
        }
    }

    void VertexArray::AddBuffer(std::unique_ptr<VertexBuffer>& buffer)
    {
        m_VertexBuffers.emplace_back(std::move(buffer));
    }

    void VertexArray::AddBuffer(std::unique_ptr<IndexBuffer>& buffer)
    {
        m_IndexBuffers.emplace_back(std::move(buffer));
    }

    void VertexArray::RemoveVertexBuffer(const u32& bufferId)
    {
        auto it = std::find_if(m_VertexBuffers.begin(), m_VertexBuffers.end(), [&bufferId](const auto& buffer)
            {
                return buffer->GetId() == bufferId;
            });

        if (it != m_VertexBuffers.end())
            m_VertexBuffers.erase(it);
    }

    void VertexArray::RemoveIndexBuffer(const u32& bufferId)
    {
        auto it = std::find_if(m_IndexBuffers.begin(), m_IndexBuffers.end(), [&bufferId](const auto& buffer)
            {
                return buffer->GetId() == bufferId;
            });

        if (it != m_IndexBuffers.end())
            m_IndexBuffers.erase(it);
    }

    VertexBuffer* VertexArray::GetVertexBuffer(const u32& bufferId)
    {
        auto it = std::find_if(m_VertexBuffers.begin(), m_VertexBuffers.end(), [&bufferId](const auto& buffer)
            {
                return buffer->GetId() == bufferId;
            });

        if (it != m_VertexBuffers.end())
            return (*it).get();

        return nullptr;
    }

    IndexBuffer* VertexArray::GetIndexBuffer(const u32& bufferId)
    {
        auto it = std::find_if(m_IndexBuffers.begin(), m_IndexBuffers.end(), [&bufferId](const auto& buffer)
            {
                return buffer->GetId() == bufferId;
            });

        if (it != m_IndexBuffers.end())
            return (*it).get();

        return nullptr;
    }


    void VertexArray::Initialize()
    {
        glGenVertexArrays(1, &m_Id);
        Bind();
    }
}