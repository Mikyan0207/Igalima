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
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetMat4(const std::string& name, const glm::mat4& matrix);

public:
	uint32_t ProgramId;
};