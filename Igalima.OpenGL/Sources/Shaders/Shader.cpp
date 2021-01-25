#include <Shaders/Shader.h>

Shader::Shader(const std::string& path, uint32_t shaderType)
{
	ShaderId = 0;

	try
	{
		std::ifstream stream(path);

		if (!stream.is_open())
		{
			std::cerr << "[Shader] Error: File not found." << std::endl;
			return;
		}

		std::string line;

		while (std::getline(stream, line))
		{
			ShaderSource += line + "\n";
		}
	}
	catch (const std::exception& ex)
	{
		std::cerr << "[Shader] Error: " << ex.what() << std::endl;
		return;
	}

	ShaderId = glCreateShader(shaderType);
	const char* src = ShaderSource.c_str();

	glShaderSource(ShaderId, 1, &src, nullptr);
	glCompileShader(ShaderId);

	int success;
	char infoLog[512];

	glGetShaderiv(ShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(ShaderId, 512, nullptr, infoLog);
		std::cerr << "[Shader] Error: " << infoLog << std::endl;
	}
}

Shader::~Shader()
{
	Delete();
}

void Shader::Delete()
{
	glDeleteShader(ShaderId);
}
