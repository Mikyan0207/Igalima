#pragma once

#include <cstdint>
#include <string>
#include <glad/glad.h>

class GLTexture
{
public:
    GLTexture(const uint32_t& width, const uint32_t& height);
    GLTexture(const std::string& path);
    GLTexture(const GLTexture&) = default;
    GLTexture(GLTexture&&) noexcept = default;
    ~GLTexture();

public:
    GLTexture& operator=(const GLTexture&) = default;
    GLTexture& operator=(GLTexture&&) noexcept = default;

public:
    void Bind(const uint32_t& slot) const;
    void Delete() const;

private:
    uint32_t m_Id;
    uint32_t m_Width;
    uint32_t m_Height;
};