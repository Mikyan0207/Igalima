//
// Created by Mikyan on 08/02/2021.
//

#include <OpenGL/GLTexture.h>

GLTexture::GLTexture(const uint32_t& width, const uint32_t& height)
{

}

GLTexture::GLTexture(const std::string& path)
{

}

GLTexture::~GLTexture()
{
    if (m_Id != 0)
        Delete();
}

void GLTexture::Bind(const uint32_t& slot) const
{
    glBindTexture(slot, m_Id);
}

void GLTexture::Delete() const
{
    glDeleteTextures(1, &m_Id);
}