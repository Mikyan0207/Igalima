//
// Created by Mikyan on 09/02/2021.
//

#ifndef IGALIMA_OPENGL_GLWRAPPER_H
#define IGALIMA_OPENGL_GLWRAPPER_H

#include <cstdint>
#include <string>
#include <glad/glad.h>

class GLWrapper
{
public:
    static void DepthFunction(const uint32_t& mode);
    static void EnableVertexAttribute(const uint32_t& index);
    static void VertexAttributePointer(const uint32_t& position, const uint32_t& size, const uint32_t& type, const uint32_t& stride, const uint32_t& offset);
    static void VertexAttributePointer(const uint32_t& programId, const std::string& name, const uint32_t& size, const uint32_t& type, const uint32_t& stride, const uint32_t& offset);
    static void DrawArray(const uint32_t& type, const uint32_t& first, const uint32_t& count);
    static void DrawElements(const uint32_t& mode, const uint32_t& count, const uint32_t& type, const void* indices);
};

#endif //IGALIMA_OPENGL_GLWRAPPER_H
