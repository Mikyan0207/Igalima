#include <OpenGL/GLVertexBuffer.h>

GLVertexBuffer::GLVertexBuffer(f32* vertices, u32 size, u32 drawMode)
{
    glGenBuffers(1, &Id);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, vertices, drawMode);
}

GLVertexBuffer::~GLVertexBuffer()
{
    glDeleteBuffers(1, &Id);
}

void GLVertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, Id);
}

void GLVertexBuffer::Unbind()
{
    glBindBuffer(GL_VERTEX_ARRAY, 0);
}