#pragma once

#include <cstdint>
#include <vector>
#include <glad/glad.h>

enum class GLVertexBufferDrawMode
{
    STATIC = GL_STATIC_DRAW,
    DYNAMIC = GL_DYNAMIC_DRAW
};

class GLVertexBuffer
{
public:
    GLVertexBuffer(const uint32_t& size, const GLVertexBufferDrawMode& mode);
    GLVertexBuffer(const float* vertices, const uint32_t& size, const GLVertexBufferDrawMode& mode);
    GLVertexBuffer(const std::vector<float>& vertices, const GLVertexBufferDrawMode& mode);
    GLVertexBuffer(const GLVertexBuffer&) = default;
    GLVertexBuffer(GLVertexBuffer&&) noexcept = default;
    ~GLVertexBuffer();

public:
    GLVertexBuffer& operator=(const GLVertexBuffer&) = default;
    GLVertexBuffer& operator=(GLVertexBuffer&&) noexcept = default;

public:
    void Bind() const;
    void Unbind() const;
    void Delete() const;

public:
    const uint32_t& GetId() const;

private:
    uint32_t m_Id;
};