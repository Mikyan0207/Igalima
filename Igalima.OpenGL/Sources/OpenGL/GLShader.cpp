#include <OpenGL/GLShader.h>

GLShader::GLShader(const std::string& vertexPath, const std::string& fragmentPath)
{
	VertexShaderId = 0;
	FragmentShaderId = 0;
	ProgramId = 0;

	try
	{
		ProgramId = glCreateProgram();

		LoadShader(vertexPath, GL_VERTEX_SHADER);
		LoadShader(fragmentPath, GL_FRAGMENT_SHADER);
		Link();
		Delete();
	}
	catch (const std::exception& ex)
	{
		std::cerr << "[GLShader] Error: " << ex.what() << std::endl;
		return;
	}
}

GLShader::~GLShader()
{
	Delete();
}

void GLShader::Use() const
{
	glUseProgram(ProgramId);
}

void GLShader::Delete() const
{
	glDeleteShader(VertexShaderId);
	glDeleteShader(FragmentShaderId);
}

void GLShader::SetBool(const std::string& name, const bool value) const
{
	glUniform1i(glGetUniformLocation(ProgramId, name.c_str()), static_cast<int>(value));
}

void GLShader::SetInt(const std::string& name, const int value) const
{
	glUniform1i(glGetUniformLocation(ProgramId, name.c_str()), value);
}

void GLShader::SetFloat(const std::string& name, const float value) const
{
	glUniform1f(glGetUniformLocation(ProgramId, name.c_str()), value);
}

void GLShader::SetMat4(const std::string& name, const glm::mat4& matrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(ProgramId, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void GLShader::SetVec3(const std::string& name, const glm::vec3& vec3) const
{
	glUniform3fv(glGetUniformLocation(ProgramId, name.c_str()), 1, &vec3[0]);
}

void GLShader::SetVec4(const std::string& name, const glm::vec4& vec4) const
{
	glUniform4fv(glGetUniformLocation(ProgramId, name.c_str()), 1, &vec4[0]);
}

void GLShader::CheckErrors(const uint32_t& shaderId)
{
	int success;
	char infoLog[512];

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
		std::cerr << "[GLShader] Error: " << infoLog << std::endl;
	}
}

void GLShader::LoadShader(const std::string& path, const uint32_t& type)
{
	std::ifstream stream(path);

	if (!stream.is_open())
	{
		std::cerr << "[GLShader] Error: File not found." << std::endl;
		return;
	}

	std::string line, content;
	while (std::getline(stream, line))
		content += line + "\n";

	auto src = content.c_str();

	if (type == GL_VERTEX_SHADER)
	{
		VertexShaderId = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(VertexShaderId, 1, &src, nullptr);
		glCompileShader(VertexShaderId);
		CheckErrors(VertexShaderId);
		glAttachShader(ProgramId, VertexShaderId);

	}
	else if (type == GL_FRAGMENT_SHADER)
	{
		FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(FragmentShaderId, 1, &src, nullptr);
		glCompileShader(FragmentShaderId);
		CheckErrors(FragmentShaderId);
		glAttachShader(ProgramId, FragmentShaderId);
	}
}

void GLShader::Link() const
{
	glLinkProgram(ProgramId);

	int success;
	char infoLog[512];

	glGetProgramiv(ProgramId, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(ProgramId, 512, nullptr, infoLog);
		std::cerr << "[GLShader] Error: " << infoLog << std::endl;
	}
}
