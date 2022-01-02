#include "TransformComponent.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Architect
{
	TransformComponent::TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
		: m_Position(position), m_Rotation(rotation), m_Scale(scale)
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

	void TransformComponent::SetScale(glm::vec3 scale)
	{
		m_Scale = scale;
	}

	void TransformComponent::Translate(glm::vec3 direction)
	{
		m_Position = m_Position + direction;
	}

	void TransformComponent::Rotate(glm::vec3 rotation)
	{
		m_Rotation = m_Rotation + rotation;
	}

	void TransformComponent::Scale(float scale)
	{
		m_Scale *= scale;
	}

	glm::mat4 TransformComponent::GetTransformMatrix() const
	{
		glm::mat4 transform(1.0f);
		transform = glm::translate(transform, m_Position);
		transform = glm::scale(transform, m_Scale);
		
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), { 1, 0, 0 })
			* glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), { 0, 1, 0 })
			* glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), { 0, 0, 1 });

		transform = transform * rotation;

		return transform;
	}
}