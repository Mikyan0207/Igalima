//
// Created by Mikyan on 08/02/2021.
//

#ifndef IGALIMA_OPENGL_GLFRAMEBUFFER_H
#define IGALIMA_OPENGL_GLFRAMEBUFFER_H

#include <cstdint>
#include <iostream>
#include <glad/glad.h>

class GLFramebuffer
{
public:
    GLFramebuffer(const uint32_t& width, const uint32_t& height);
    GLFramebuffer(const GLFramebuffer&) = default;
    GLFramebuffer(GLFramebuffer&&) noexcept = default;
    ~GLFramebuffer();

public:
    GLFramebuffer& operator=(const GLFramebuffer&) = default;
    GLFramebuffer& operator=(GLFramebuffer&&) noexcept = default;

public:
    void Bind() const;
    void Unbind() const;
    void Delete() const;

public:
    const uint32_t& GetId() const;
    const uint32_t& GetColorAttachmentId() const;
    const uint32_t& GetRenderBufferId() const;

private:
    uint32_t m_Id;
    uint32_t m_ColorAttachmentId;
    uint32_t m_RenderBufferId;
    uint32_t m_Width;
    uint32_t m_Height;
};

#endif //IGALIMA_OPENGL_GLFRAMEBUFFER_H
