#include "TransformComponent.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Architect
{
	TransformComponent::TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :
		Position(position), Rotation(rotation), Scale(scale), 
		LocalToWorld(glm::mat4(1.0f)), LocalToParent(glm::mat4(1.0f))
	{
	}

	void TransformComponent::Translate(glm::vec3 direction)
	{
		Position += direction;
	}

	void TransformComponent::Rotate(glm::vec3 rotation)
	{
		Rotation += rotation;
	}

	void TransformComponent::Dilate(float scale)
	{
		Scale *= scale;
	}

	void TransformComponent::Dilate(glm::vec3 scale)
	{
		Scale *= scale;
	}
}