//
// Created by Mikyan on 07/02/2021.
//

#include <OpenGL/GLVertexBuffer.h>

GLVertexBuffer::GLVertexBuffer(const uint32_t& size, const GLVertexBufferDrawMode& mode)
{
    glGenBuffers(1, &m_Id);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, static_cast<GLenum>(mode));
}

GLVertexBuffer::GLVertexBuffer(const float* vertices, const uint32_t& size, const GLVertexBufferDrawMode& mode)
{
    glGenBuffers(1, &m_Id);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, vertices, static_cast<GLenum>(mode));
}

GLVertexBuffer::~GLVertexBuffer()
{
    Delete();
}

void GLVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
}

void GLVertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLVertexBuffer::Delete() const
{
    glDeleteBuffers(1, &m_Id);
}

const uint32_t& GLVertexBuffer::GetId() const
{
    return m_Id;
}