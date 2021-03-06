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
	Terrain(const float& renderSize, const uint32_t& dim, const uint32_t& heightmapId);
	Terrain(const Terrain&) = default;
	Terrain(Terrain&&) noexcept = default;
	~Terrain();
    
    public:
	Terrain& operator=(const Terrain&) = default;
	Terrain& operator=(Terrain&&) noexcept = default;
    
    public:
    void Draw();
	void SetMVP(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
    
    private:
	uint32_t m_Size;
	uint32_t m_VerticesCount;
	uint32_t m_IndicesCount;
	uint32_t m_TextureCoordinatesCount;
	GLVertexArray m_VertexArray;
	GLShader m_Shader;
    
	// Textures
	uint32_t m_HeightmapId;
	Texture* m_Heightmap;
	Texture* m_GrassTexture;
    // Add Dirt Texture?
    Texture* m_StoneTexture;
    Texture* m_SnowTexture;
};