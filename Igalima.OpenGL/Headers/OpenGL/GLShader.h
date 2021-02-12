#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <iostream>
#include <fstream>

class GLShader
{
public:
	GLShader() = default;
	GLShader(const std::string& vertexPath, const std::string& fragmentPath);
	GLShader(const GLShader&) = default;
	GLShader(GLShader&&) noexcept = default;
	~GLShader();

public:
	GLShader& operator=(const GLShader&) = default;
	GLShader& operator=(GLShader&&) noexcept = default;

public:
	void Use() const;
	void Unbind() const;
	void Delete() const;

	GLShader& SetBool(const std::string& name, bool value);
	GLShader& SetInt(const std::string& name, int value);
	GLShader& SetFloat(const std::string& name, float value);
	GLShader& SetMat4(const std::string& name, const glm::mat4& matrix);
	GLShader& SetVec3(const std::string& name, const glm::vec3& vec3);
	GLShader& SetVec4(const std::string& name, const glm::vec4& vec4);

private:
	static void CheckErrors(const uint32_t& shaderId);
	void LoadShader(const std::string& path, const uint32_t& type);
	void Link() const;

public:
	uint32_t ProgramId;
	uint32_t VertexShaderId;
	uint32_t FragmentShaderId;
};