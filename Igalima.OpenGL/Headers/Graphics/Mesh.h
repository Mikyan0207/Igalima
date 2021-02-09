#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <OpenGL/Vertex.h>
#include <OpenGL/GLShader.h>
#include <OpenGL/GLColor.h>

struct OGLTexture
{
	uint32_t Id;
	std::string Path;
	std::string Type;
};

class Mesh
{
	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<OGLTexture>& textures, std::unordered_map<std::string, GLColor> colors);
		Mesh(const Mesh&) = default;
		Mesh(Mesh&&) noexcept = default;
		~Mesh() = default;

	public:
		Mesh& operator=(const Mesh&) = default;
		Mesh& operator=(Mesh&&) noexcept = default;

	public:
		void Draw(GLShader& shader);

	public:
		std::vector<Vertex> Vertices;
		std::vector<uint32_t> Indices;
		std::vector<OGLTexture> Textures;
	private:
		uint32_t m_VertexArrayObject;
		uint32_t m_VertexBufferObject;
		uint32_t m_ElementBufferObject;
		std::unordered_map<std::string, GLColor> m_Colors;

};
