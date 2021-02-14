#include <Components/Transform.h>

Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	Position = position;
	Rotation = rotation;
	Scale = scale;
}