#pragma once

#include <cstdint>
#include <vector>
#include <glad/glad.h>
#include <OpenGL/GLDrawMode.h>

class GLVertexBuffer
{
public:
    GLVertexBuffer(const uint32_t& size, const GLDrawMode& mode);
    GLVertexBuffer(const float* vertices, const uint32_t& size, const GLDrawMode& mode);
    GLVertexBuffer(const std::vector<float>& vertices, const GLDrawMode& mode);
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