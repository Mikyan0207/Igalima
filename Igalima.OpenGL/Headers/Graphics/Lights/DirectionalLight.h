#pragma once

#include <glm/glm.hpp>

class DirectionalLight
{
public:
	DirectionalLight(const glm::vec3& direction);
	DirectionalLight(const DirectionalLight&) = default;
	DirectionalLight(DirectionalLight&&) noexcept = default;
	~DirectionalLight() = default;

public:
	DirectionalLight& operator=(const DirectionalLight&) = default;
	DirectionalLight& operator=(DirectionalLight&&) noexcept = default;

private:
	glm::vec3 m_Direction;
};