//
// Created by Mikyan on 09/02/2021.
//

#include <OpenGL/GLWrapper.h>

void GLWrapper::Viewport(const int& x, const int& y, const uint32_t& width, const uint32_t& height)
{
    glViewport(x, y, width, height);
}

void GLWrapper::DepthFunction(const uint32_t& mode)
{
    glDepthFunc(mode);
}

void GLWrapper::EnableVertexAttribute(const uint32_t& index)
{
    glEnableVertexAttribArray(index);
}

void GLWrapper::VertexAttributePointer(const uint32_t& position, const uint32_t& size, const uint32_t& type, const uint32_t& stride, const uint32_t& offset)
{
    glVertexAttribPointer(position, size, type, GL_FALSE, stride, reinterpret_cast<void*>(offset));

    // @Note:
    // Maybe we want to manually call EnableVertexAttribute?
    GLWrapper::EnableVertexAttribute(position);
}

void GLWrapper::VertexAttributePointer(const uint32_t& programId, const std::string& name, const uint32_t& size, const uint32_t& type, const uint32_t& stride, const uint32_t& offset)
{
    const auto pos = glGetAttribLocation(programId, name.c_str());

    GLWrapper::VertexAttributePointer(pos, size, type, stride, offset);
}

void GLWrapper::DrawArray(const uint32_t& type, const uint32_t& first, const uint32_t& count)
{
    glDrawArrays(type, first, count);
}

void GLWrapper::DrawElements(const uint32_t& mode, const uint32_t& count, const uint32_t& type, const void* indices)
{
    glDrawElements(static_cast<GLenum>(mode), count, static_cast<GLenum>(type), indices);
}