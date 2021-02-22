#include <OpenGL/GLVertexArray.h>

GLVertexArray::GLVertexArray()
{
    glGenVertexArrays(1, &Id);
}

GLVertexArray::~GLVertexArray()
{
    glDeleteVertexArrays(1, &Id);
}

void GLVertexArray::Bind()
{
    glBindVertexArray(Id);
}

void GLVertexArray::Unbind()
{
    glBindVertexArray(0);
}