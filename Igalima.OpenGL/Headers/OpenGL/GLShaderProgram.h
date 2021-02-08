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
#include <glm/glm.hpp>
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
    void Use();
    void Link();
    void Delete();

public:
    void SetBool(const std::string& name, const bool value);
    void SetInt(const std::string& name, const int& value);
    void SetFloat(const std::string& name, const float& value);
    void SetVec3(const std::string& name, const glm::vec3& value);
    void SetVec4(const std::string& name, const glm::vec4& value);
    void SetMat4(const std::string& name, const glm::mat4& value);

private:
    uint32_t m_Id;
    std::vector<uint32_t> m_Shaders;
};

#endif //IGALIMA_OPENGL_GLSHADERPROGRAM_H
