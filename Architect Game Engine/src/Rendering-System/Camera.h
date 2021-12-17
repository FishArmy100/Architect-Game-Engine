#pragma once
#include "glm/mat4x4.hpp"

namespace Architect
{
	class Camera
	{
	private:
		static Camera* m_MainCamera;

		glm::vec3 m_Position;
		float m_Rotation;

		glm::mat4 m_ProjectionMatrix;


	public:
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; }

		const float GetRotation() const { return m_Rotation; }
		void SetRotation(const float rotation) { m_Rotation = rotation; }

		Camera(float left, float right, float bottom, float top);
		void SetAsMain();
		glm::mat4 GetViewProjection() const;

		static const Camera* GetMainCamera();
	};
}

