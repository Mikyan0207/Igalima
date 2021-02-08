//
// Created by Mikyan on 08/02/2021.
//

#include <OpenGL/GLShaderProgram.h>

GLShaderProgram::GLShaderProgram()
{
    m_Id = glCreateProgram();
}

GLShaderProgram::~GLShaderProgram()
{
    Delete();
}

void GLShaderProgram::AddShader(const GLShader& shader)
{
    m_Shaders.emplace_back(shader.GetVertexId());
    m_Shaders.emplace_back(shader.GetFragmentId());

    glAttachShader(m_Id, shader.GetVertexId());
    glAttachShader(m_Id, shader.GetFragmentId());
}

void GLShaderProgram::Use()
{
    glUseProgram(m_Id);
}

void GLShaderProgram::Link()
{
    glLinkProgram(m_Id);

    int success;
    char infoLog[512];

    glGetProgramiv(m_Id, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(m_Id, 512, nullptr, infoLog);
        std::cerr << "[Shader Program] Error: " << infoLog << std::endl;
    }
}

void GLShaderProgram::Delete()
{
    glDeleteProgram(m_Id);
}

void GLShaderProgram::SetBool(const std::string& name, const bool value)
{
    glUniform1i(glGetUniformLocation(m_Id, name.c_str()), static_cast<int>(value));
}

void GLShaderProgram::SetInt(const std::string& name, const int& value)
{
    glUniform1i(glGetUniformLocation(m_Id, name.c_str()), value);
}

void GLShaderProgram::SetFloat(const std::string& name, const float& value)
{
    glUniform1f(glGetUniformLocation(m_Id, name.c_str()), value);
}

void GLShaderProgram::SetVec3(const std::string& name, const glm::vec3& value)
{
    glUniform3fv(glGetUniformLocation(m_Id, name.c_str()), 1, &value[0]);
}

void GLShaderProgram::SetVec4(const std::string& name, const glm::vec4& value)
{
    glUniform4fv(glGetUniformLocation(m_Id, name.c_str()), 1, &value[0]);
}

void GLShaderProgram::SetMat4(const std::string& name, const glm::mat4& value)
{
    glUniformMatrix4fv(glGetUniformLocation(m_Id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}