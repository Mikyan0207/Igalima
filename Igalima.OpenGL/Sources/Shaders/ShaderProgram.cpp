#include <Shaders/ShaderProgram.h>

ShaderProgram::ShaderProgram()
{
	ProgramId = 0;

	ProgramId = glCreateProgram();
}

void ShaderProgram::Attach(Shader& shader)
{
	glAttachShader(ProgramId, shader.ShaderId);
}

void ShaderProgram::Link()
{
	glLinkProgram(ProgramId);

	int success;
	char infoLog[512];

	glGetProgramiv(ProgramId, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(ProgramId, 512, nullptr, infoLog);
		std::cerr << "[ShaderProgram] Error: " << infoLog << std::endl;
	}
}

void ShaderProgram::Use()
{
	glUseProgram(ProgramId);
}

void ShaderProgram::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ProgramId, name.c_str()), static_cast<int>(value));
}

void ShaderProgram::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ProgramId, name.c_str()), value);
}

void ShaderProgram::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ProgramId, name.c_str()), value);
}

void ShaderProgram::SetMat4(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(ProgramId, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}