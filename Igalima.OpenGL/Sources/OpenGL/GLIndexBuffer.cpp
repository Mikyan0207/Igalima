#include <OpenGL/GLIndexBuffer.h>

GLIndexBuffer::GLIndexBuffer(const uint32_t* indices, const uint32_t& size, const GLDrawMode& mode)
{
	glGenBuffers(1, &m_Id);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, static_cast<GLenum>(mode));
}

GLIndexBuffer::GLIndexBuffer(const std::vector<uint32_t>& indices, const GLDrawMode& mode)
{
	glGenBuffers(1, &m_Id);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), static_cast<GLenum>(mode));
}

GLIndexBuffer::~GLIndexBuffer()
{
	Delete();
}

void GLIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
}

void GLIndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLIndexBuffer::Delete() const
{
	if (m_Id != 0)
		glDeleteBuffers(1, &m_Id);
}

const uint32_t& GLIndexBuffer::GetId() const
{
	return m_Id;
}