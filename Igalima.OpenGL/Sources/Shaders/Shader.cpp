#include <Shaders/Shader.h>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
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
		std::cerr << "[Shader] Error: " << ex.what() << std::endl;
		return;
	}
}

Shader::~Shader()
{
	Delete();
}

void Shader::Use()
{
	glUseProgram(ProgramId);
}

void Shader::Delete()
{
	glDeleteShader(VertexShaderId);
	glDeleteShader(FragmentShaderId);
}

void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ProgramId, name.c_str()), static_cast<int>(value));
}

void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ProgramId, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ProgramId, name.c_str()), value);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(ProgramId, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& vec3)
{
	glUniform3fv(glGetUniformLocation(ProgramId, name.c_str()), 1, &vec3[0]);
}

void Shader::CheckErrors(const uint32_t& shaderId)
{
	int success;
	char infoLog[512];

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
		std::cerr << "[Shader] Error: " << infoLog << std::endl;
	}
}

void Shader::LoadShader(const std::string& path, const uint32_t& type)
{
	std::ifstream stream(path);

	if (!stream.is_open())
	{
		std::cerr << "[Shader] Error: File not found." << std::endl;
		return;
	}

	std::string line, content;
	while (std::getline(stream, line))
		content += line + "\n";

	const char* src = content.c_str();

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

void Shader::Link()
{
	glLinkProgram(ProgramId);

	int success;
	char infoLog[512];

	glGetProgramiv(ProgramId, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(ProgramId, 512, nullptr, infoLog);
		std::cerr << "[Shader] Error: " << infoLog << std::endl;
	}
}
