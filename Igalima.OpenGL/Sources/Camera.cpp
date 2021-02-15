#include <Camera.h>

Camera::Camera(const glm::vec3& position, const glm::vec3& up)
{
	Position = position;
	WorldUp = up;
	Pitch = 0.0f;
	Yaw = -90.0f;
	Speed = 30.5f;
	FOV = 65.0f;
	MouseSensitivity = 0.1f;

	Update();
}

void Camera::Update()
{
	Front = glm::normalize(glm::vec3 {
		cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)),
		sin(glm::radians(Pitch)),
		sin(glm::radians(Yaw)) * cos(glm::radians(Pitch))
		});
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}

void Camera::ProcessMouseEvents(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;
	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	Update();
}

void Camera::ProcessKeyboardEvents(const CameraDirection& direction, const float& deltaTime)
{
	float velocity = Speed * deltaTime;

	if (direction == CameraDirection::FORWARD)
		Position += Front * velocity;
	if (direction == CameraDirection::BACKWARD)
		Position -= Front * velocity;
	if (direction == CameraDirection::LEFT)
		Position -= Right * velocity;
	if (direction == CameraDirection::RIGHT)
		Position += Right * velocity;
}

void Camera::ProcessScrollEvents(const float& yoffset)
{
	FOV -= yoffset;

	if (FOV < 1.0f)
		FOV = 1.0f;
	if (FOV > 99.0f)
		FOV = 99.0f;
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(Position, Position + Front, Up);
}
