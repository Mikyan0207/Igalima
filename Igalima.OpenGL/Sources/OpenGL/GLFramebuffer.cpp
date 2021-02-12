//
// Created by Mikyan on 08/02/2021.
//

#include <OpenGL/GLFramebuffer.h>

GLFramebuffer::GLFramebuffer(const uint32_t& width, const uint32_t& height)
{
    m_Width = width;
    m_Height = height;

    // Color Attachment.
    glGenTextures(1,&m_ColorAttachmentId);
    glBindTexture(GL_TEXTURE_2D, m_ColorAttachmentId);

    // Create Texture for color attachment
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, m_Width, m_Height, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Create Render Buffer.
    glGenRenderbuffers(1, &m_RenderBufferId);
    glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, m_Width, m_Height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    // Link everything to framebuffer.
    glGenFramebuffers(1, &m_Id);
    Bind();

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachmentId, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RenderBufferId);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << "[Framebuffer] Incomplete framebuffer!" << std::endl;
    }

    Unbind();
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

const uint32_t& GLFramebuffer::GetId() const
{
    return m_Id;
}

const uint32_t& GLFramebuffer::GetColorAttachmentId() const
{
    return m_ColorAttachmentId;
}

const uint32_t& GLFramebuffer::GetRenderBufferId() const
{
    return m_RenderBufferId;
}