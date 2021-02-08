//
// Created by Mikyan on 08/02/2021.
//

#ifndef IGALIMA_OPENGL_GLFRAMEBUFFER_H
#define IGALIMA_OPENGL_GLFRAMEBUFFER_H

#include <cstdint>
#include <glad/glad.h>

class GLFramebuffer
{
public:
    GLFramebuffer();
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

private:
    uint32_t m_Id;
};

#endif //IGALIMA_OPENGL_GLFRAMEBUFFER_H
