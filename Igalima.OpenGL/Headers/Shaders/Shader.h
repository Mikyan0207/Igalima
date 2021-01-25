#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <iostream>
#include <fstream>

class Shader
{
public:
	Shader(const std::string& path, uint32_t shaderType);
	~Shader();

public:
	void Delete();

public:
	uint32_t ShaderId;
	std::string ShaderSource;
};