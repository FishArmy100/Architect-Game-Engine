#pragma once
#include "glm/ext.hpp"

namespace Architect
{
	class TransformComponent
	{
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;

	public:
		TransformComponent(glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0));
		~TransformComponent();
		TransformComponent(const TransformComponent& other) = default;

		glm::vec3 GetPosition() const { return m_Position; }
		void SetPosition(glm::vec3 position);

		glm::vec3 GetRotation() const { return m_Rotation; }
		void SetRotation(glm::vec3 rotation);

		void Translate(glm::vec3 direction);
		void Rotation(glm::vec3 rotation);

		glm::mat4 GetTransformMatrix() const;
	};
}

