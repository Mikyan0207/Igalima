//
// Created by Mikyan on 08/02/2021.
//

#include <OpenGL/GLVertexArray.h>

GLVertexArray::GLVertexArray()
{
    glGenVertexArrays(1, &m_Id);

    // Bind VAO at creation?
    Bind();
}

GLVertexArray::~GLVertexArray()
{
    Delete();
}

void GLVertexArray::Bind() const
{
    glBindVertexArray(m_Id);
}

void GLVertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void GLVertexArray::Delete() const
{
    glDeleteVertexArrays(1, &m_Id);
}

// Maybe I should check the buffer type to avoid duplicates?
void GLVertexArray::AddBuffer(std::unique_ptr<GLVertexBuffer>& buffer)
{
    m_Buffers.emplace_back(std::move(buffer));
}

void GLVertexArray::RemoveBuffer(const uint32_t& bufferId)
{
    auto it = std::find_if(m_Buffers.begin(), m_Buffers.end(), [&bufferId](const auto& buffer)
    {
        return buffer->GetId() == bufferId;
    });

    if (it != m_Buffers.end())
        m_Buffers.erase(it);
}

GLVertexBuffer* GLVertexArray::GetBuffer(const uint32_t& bufferId)
{
    auto it = std::find_if(m_Buffers.begin(), m_Buffers.end(), [&bufferId](const auto& buffer)
    {
        return buffer->GetId() == bufferId;
    });

    if (it != m_Buffers.end())
        return (*it).get();

    return nullptr;
}
