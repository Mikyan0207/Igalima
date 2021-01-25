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
