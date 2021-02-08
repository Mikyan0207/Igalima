//
// Created by Mikyan on 08/02/2021.
//

#include <OpenGL/GLFramebuffer.h>

GLFramebuffer::GLFramebuffer()
{
    glGenFramebuffers(1, &m_Id);
    Bind();
}

GLFramebuffer::~GLFramebuffer()
{
    Delete();
}

void GLFramebuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
}

void GLFramebuffer::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GLFramebuffer::Delete() const
{
    glDeleteFramebuffers(1, &m_Id);
}