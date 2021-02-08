//
// Created by Mikyan on 08/02/2021.
//

#ifndef IGALIMA_OPENGL_GLSHADER_H
#define IGALIMA_OPENGL_GLSHADER_H

#include <cstdint>
#include <string>
#include <glad/glad.h>
#include <fstream>
#include <iostream>

class GLShader
{
public:
    GLShader(const std::string& vertexPath, const std::string& fragmentPath);
    GLShader(const GLShader&) = default;
    GLShader(GLShader&&) noexcept = default;
    ~GLShader();

public:
    GLShader& operator=(const GLShader&) = default;
    GLShader& operator=(GLShader&&) noexcept = default;

public:
    const uint32_t& GetVertexId() const;
    const uint32_t& GetFragmentId() const;

private:
    uint32_t m_VertexId;
    uint32_t m_FragmentId;
};

#endif //IGALIMA_OPENGL_GLSHADER_H
