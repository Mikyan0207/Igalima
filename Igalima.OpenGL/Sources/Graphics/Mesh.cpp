#include <Graphics/Mesh.h>

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<Texture>& textures)
{
	Vertices = vertices;
	Indices = indices;
	Textures = textures;

	m_VertexArrayObject = 0;
	m_VertexBufferObject = 0;
	m_ElementBufferObject = 0;

	glGenVertexArrays(1, &m_VertexArrayObject);
	glGenBuffers(1, &m_VertexBufferObject);
	glGenBuffers(1, &m_ElementBufferObject);

	glBindVertexArray(m_VertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(uint32_t), &Indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextureCoordinate));

	glBindVertexArray(0);
}

void Mesh::Draw(Shader& shader)
{

}