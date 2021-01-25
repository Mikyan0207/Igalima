#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraDirection {
	FORWARD, BACKWARD, LEFT, RIGHT
};

class Camera
{
public:
	Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f));
	Camera(const Camera&) = default;
	Camera(Camera&&) noexcept = default;
	~Camera() = default;

public:
	Camera& operator=(const Camera&) = default;
	Camera& operator=(Camera&&) noexcept = default;

public:
	void Update();
	void ProcessMouseEvents(float xoffset, float yoffset, bool constrainPitch = true);
	void ProcessKeyboardEvents(const CameraDirection& direction, const float& deltaTime);
	void ProcessScrollEvents(const float& yoffset);

public:
	glm::mat4 GetViewMatrix() const;

public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	
	float Yaw;
	float Pitch;

	float Speed;
	float MouseSensitivity;
	float FOV;
};