#pragma once

#include <OpenGL/GLDrawMode.h>
#include <cstdint>
#include <vector>

class GLIndexBuffer
{
public:
    GLIndexBuffer(const uint32_t* indices, const uint32_t& size, const GLDrawMode& mode);
    GLIndexBuffer(const std::vector<uint32_t>& indices, const GLDrawMode& mode);
    GLIndexBuffer(const GLIndexBuffer&) = default;
    GLIndexBuffer(GLIndexBuffer&&) noexcept = default;
    ~GLIndexBuffer();

public:
    GLIndexBuffer& operator=(const GLIndexBuffer&) = default;
    GLIndexBuffer& operator=(GLIndexBuffer&&) noexcept = default;

public:
    void Bind() const;
    void Unbind() const;
    void Delete() const;

public:
    const uint32_t& GetId() const;

private:
    uint32_t m_Id;
};