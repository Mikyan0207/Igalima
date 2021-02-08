//
// Created by Mikyan on 08/02/2021.
//

#include <OpenGL/GLShader.h>

GLShader::GLShader(const std::string& vertexPath, const std::string& fragmentPath)
{
    m_VertexId = 0;
    m_FragmentId = 0;

    LoadShader(vertexPath, GL_VERTEX_SHADER);
    LoadShader(fragmentPath, GL_FRAGMENT_SHADER);
}

GLShader::~GLShader()
{
    if (m_VertexId != 0 && m_FragmentId != 0)
        Delete();
}

void GLShader::Delete() const
{
    glDeleteShader(m_VertexId);
    glDeleteShader(m_FragmentId);
}

const uint32_t& GLShader::GetVertexId() const
{
    return m_VertexId;
}

const uint32_t& GLShader::GetFragmentId() const
{
    return m_FragmentId;
}

void GLShader::LoadShader(const std::string& path, const uint32_t& type)
{
    std::ifstream stream (path);

    if (!stream.is_open())
    {
        std::cerr << "[Shader Program] Error: File " << path << " not found." << std::endl;
        return;
    }

    std::string line, content;
    while(std::getline(stream, line))
        content += line + "\n";

    const auto* src = content.c_str();

    if (type == GL_VERTEX_SHADER)
    {
        m_VertexId = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(m_VertexId, 1, &src, nullptr);
        glCompileShader(m_VertexId);
        CheckErrors(m_VertexId);
    }
    else if (type == GL_FRAGMENT_SHADER)
    {
        m_FragmentId = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(m_FragmentId, 1, &src, nullptr);
        glCompileShader(m_FragmentId);
        CheckErrors(m_FragmentId);
    }
    else
    {
        std::cerr << "Invalid type specified." << std::endl;
    }
}

void GLShader::CheckErrors(const uint32_t& shaderId)
{
    GLint isCompiled = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);

    if (!isCompiled)
    {
        GLint maxLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(shaderId, maxLength, &maxLength, &infoLog[0]);

        std::cerr << "[Shader] Error: " << infoLog.data() << std::endl;

        // Shader is useless now, so delete it.
        glDeleteShader(shaderId);
    }
}