#pragma once
#include "glm/ext.hpp"
#include <vector>
#include "entt/entt.hpp"

namespace Architect
{
	class TransformComponent
	{
	public:
		TransformComponent(glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1));
		~TransformComponent();
		TransformComponent(const TransformComponent& other) = default;

		glm::vec3 GetPosition() const { return m_Position; }
		void SetPosition(glm::vec3 position);

		glm::vec3 GetRotation() const { return m_Rotation; }
		void SetRotation(glm::vec3 rotation);

		glm::vec3 GetScale() const { return m_Scale; }
		void SetScale(glm::vec3 scale);

		void Translate(glm::vec3 direction);
		void Rotate(glm::vec3 rotation);
		void Scale(float scale);

		glm::mat4 GetTransformMatrix() const;

	private:


	private:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;
	};
}

