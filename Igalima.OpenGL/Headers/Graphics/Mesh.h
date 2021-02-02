#pragma once

#include <vector>
#include <OpenGL/Vertex.h>
#include <OpenGL/Texture.h>
#include <Graphics/Shader.h>

class Mesh
{
	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<Texture>& textures);
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
		std::vector<Texture> Textures;

	private:
		uint32_t m_VertexArrayObject;
		uint32_t m_VertexBufferObject;
		uint32_t m_ElementBufferObject;
};