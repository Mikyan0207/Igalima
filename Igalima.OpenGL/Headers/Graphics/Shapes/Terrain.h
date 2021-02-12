#pragma once

#include <cstdint>
#include <vector>
#include <glm/glm.hpp>
#include <OpenGL/GLWrapper.h>
#include <OpenGL/GLVertexArray.h>
#include <OpenGL/GLVertexBuffer.h>
#include <OpenGL/GLIndexBuffer.h>
#include <OpenGL/GLShader.h>
#include <Graphics/Textures/Texture.h>

class Terrain
{
public:
	Terrain(const uint32_t& size);
	Terrain(const Terrain&) = default;
	Terrain(Terrain&&) noexcept = default;
	~Terrain();

public:
	Terrain& operator=(const Terrain&) = default;
	Terrain& operator=(Terrain&&) noexcept = default;

public:
    void Draw(const uint32_t& textureId);
	void SetMVP(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);

private:
	uint32_t m_Size;
	uint32_t m_VerticesCount;
	uint32_t m_IndicesCount;
	uint32_t m_TextureCoordinatesCount;
	GLVertexArray m_VertexArray;
	GLShader m_Shader;

	Texture* heightmap;

};