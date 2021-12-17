#include "TransformComponent.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Architect
{
	TransformComponent::TransformComponent(glm::vec3 position, glm::vec3 rotation)
		: m_Position(position), m_Rotation(rotation)
	{
	}

	TransformComponent::~TransformComponent()
	{

	}

	void TransformComponent::SetPosition(glm::vec3 position)
	{
		m_Position = position;
	}

	void TransformComponent::SetRotation(glm::vec3 rotation)
	{
		m_Rotation = rotation;
	}

	void TransformComponent::Translate(glm::vec3 direction)
	{
		m_Position = m_Position + direction;
	}

	void TransformComponent::Rotation(glm::vec3 rotation)
	{
		m_Rotation = m_Rotation + rotation;
	}

	glm::mat4 TransformComponent::GetTransformMatrix() const
	{
		glm::mat4 transform(1.0f);
		transform = glm::translate(transform, m_Position);
		return transform;
	}
}