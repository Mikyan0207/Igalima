//
// Created by Mikyan on 08/02/2021.
//

#ifndef IGALIMA_OPENGL_GLSHADERPROGRAM_H
#define IGALIMA_OPENGL_GLSHADERPROGRAM_H

#include <cstdint>
#include <string>
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <OpenGL/GLShader.h>

// @Incomplete: Check this again later.
// Sometimes having multiples shaders sharing the same program is useful for
// specific effects (?)
class GLShaderProgram
{
public:
    GLShaderProgram();
    GLShaderProgram(const GLShaderProgram&) = default;
    GLShaderProgram(GLShaderProgram&&) noexcept = default;
    ~GLShaderProgram();

public:
    GLShaderProgram& operator=(const GLShaderProgram&) = default;
    GLShaderProgram& operator=(GLShaderProgram&&) noexcept = default;

public:
    void AddShader(const GLShader& shader);
    void AddShader(const uint32_t& shaderId);
    void AddShader(const uint32_t& vertexId, const uint32_t& fragmentId);
    void Bind(const uint32_t& id);
    void Bind(const GLShader& shader);
    void Delete();

private:
    uint32_t m_Id;
    std::vector<uint32_t> m_Shaders;
};

#endif //IGALIMA_OPENGL_GLSHADERPROGRAM_H
