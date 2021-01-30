#pragma once

#include <glm/glm.hpp>
#include <vector>

class Cube
{
public:
	Cube(const float& size);
	Cube(const Cube&) = default;
	Cube(Cube&&) noexcept = default;
	~Cube() = default;

private:
	std::vector<glm::vec3> m_Vertices;
	std::vector<glm::vec3> m_Normals;
};