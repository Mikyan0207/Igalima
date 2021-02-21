#include <OpenGL/GLIndexBuffer.h>


GLIndexBuffer::GLIndexBuffer(u32* indices, u32 size, u32 drawMode)
{
    glGenBuffers(1, &Id);
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, drawMode);
}

GLIndexBuffer::~GLIndexBuffer()
{
    glDeleteBuffers(1, &Id);
}

void GLIndexBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id);
}

void GLIndexBuffer::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}