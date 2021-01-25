#pragma once

#include <glad/glad.h>

#include <cstdint>

#include <Shaders/Shader.h>

class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(const ShaderProgram&) = default;
	ShaderProgram(ShaderProgram&&) = default;
	~ShaderProgram() = default;

public:
	ShaderProgram& operator=(const ShaderProgram&) = default;
	ShaderProgram& operator=(ShaderProgram&&) noexcept = default;

public:
	void Attach(Shader& shader);
	void Link();
	void Use();

public:
	uint32_t ProgramId;
};