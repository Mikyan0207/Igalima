#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <algorithm>
#include <glad/glad.h>

#include <OpenGL/GLVertexBuffer.h>
#include <OpenGL/GLIndexBuffer.h>

class GLVertexArray
{
public:
    GLVertexArray();
    GLVertexArray(const GLVertexArray&) = default;
    GLVertexArray(GLVertexArray&&) noexcept = default;
    ~GLVertexArray();

public:
    GLVertexArray& operator=(const GLVertexArray&) = default;
    GLVertexArray& operator=(GLVertexArray&&) noexcept = default;

public:
    void Bind() const;
    void Unbind() const;
    void Delete() const;
    void AddBuffer(std::unique_ptr<GLVertexBuffer>& buffer);
    void AddBuffer(std::unique_ptr<GLIndexBuffer>& buffer);
    void RemoveBuffer(const uint32_t& bufferId);

public:
    GLVertexBuffer* GetBuffer(const uint32_t& bufferId);
    GLIndexBuffer* GetIndexBuffer(const uint32_t& bufferId);

private:
    uint32_t m_Id;
    std::vector<std::unique_ptr<GLVertexBuffer>> m_Buffers;
    std::vector<std::unique_ptr<GLIndexBuffer>> m_IndexBuffers;
};