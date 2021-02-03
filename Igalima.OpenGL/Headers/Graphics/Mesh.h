#pragma once

#include <vector>
#include <unordered_map>
#include <OpenGL/Vertex.h>
#include <OpenGL/GLTexture.h>
#include <Graphics/Shader.h>
#include <OpenGL/GLColor.h>

class Mesh
{
	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<GLTexture>& textures, std::unordered_map<std::string, GLColor> colors);
		Mesh(const Mesh&) = default;
		Mesh(Mesh&&) noexcept = default;
		~Mesh() = default;

	public:
		Mesh& operator=(const Mesh&) = default;
		Mesh& operator=(Mesh&&) noexcept = default;

	public:
		void Draw(Shader& shader);

	public:
		std::vector<Vertex> Vertices;
		std::vector<uint32_t> Indices;
		std::vector<GLTexture> Textures;
	private:
		uint32_t m_VertexArrayObject;
		uint32_t m_VertexBufferObject;
		uint32_t m_ElementBufferObject;
		std::unordered_map<std::string, GLColor> m_Colors;

};
