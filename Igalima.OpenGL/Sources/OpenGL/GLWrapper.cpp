//
// Created by Mikyan on 09/02/2021.
//

#include <OpenGL/GLWrapper.h>

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

void GLWrapper::DrawArray(const uint32_t& type, const uint32_t& first, const uint32_t& count)
{
    glDrawArrays(type, first, count);
}