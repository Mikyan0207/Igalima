//
// Created by Mikyan on 13/02/2021.
//

#ifndef IGALIMA_OPENGL_TRANSFORM_H
#define IGALIMA_OPENGL_TRANSFORM_H

#include <glm/glm.hpp>

#include <Components/Component.h>

struct Transform : public Component
{
	Transform(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& rotation = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f));
	Transform(const Transform&) = default;
	Transform(Transform&&) noexcept = default;
	~Transform() = default;

	Transform& operator=(const Transform&) = default;
	Transform& operator=(Transform&&) noexcept = default;

	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;
};

#endif //IGALIMA_OPENGL_TRANSFORM_H
