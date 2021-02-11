#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <OpenGL/GLWrapper.h>
#include <OpenGL/GLShader.h>
#include <OpenGL/GLVertexArray.h>
#include <OpenGL/GLVertexBuffer.h>

struct NoiseSettings
{
	float Height;
	float Lacunary;
	float Octaves;
	float Offset;
	float Gain;
	float Density;
	std::string VertexShaderPath;
	std::string FragmentShaderPath;
};

class Noise
{
public:
	Noise();
	Noise(const NoiseSettings& settings);
	Noise(const Noise&) = default;
	Noise(Noise&&) noexcept = default;
	~Noise();

public:
	Noise& operator=(const Noise&) = default;
	Noise& operator=(Noise&&) noexcept = default;

public:
	void Draw();

private:
	void Initialize();
	void SetUniforms();

private:
	NoiseSettings m_Settings;
	GLShader m_Shader;
	GLVertexArray m_VertexArray;
};