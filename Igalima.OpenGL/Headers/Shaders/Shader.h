#pragma once

#include <glad/glad.h>

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
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;

public:
	uint32_t ShaderId;
	std::string ShaderSource;
};