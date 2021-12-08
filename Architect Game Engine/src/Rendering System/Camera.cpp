#include "Camera.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Architect
{
	Camera* Camera::m_MainCamera;

	Camera::Camera(float left, float right, float bottom, float top)
	{
		m_Position = glm::vec3(0, 0, 0);
		m_Rotation = 0;
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top);

		if (m_MainCamera == nullptr)
			SetAsMain();
	}

	void Camera::SetAsMain()
	{
		m_MainCamera = this;
	}

	glm::mat4 Camera::GetViewProjection() const
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) 
			* glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0, 0, 1));

		glm::mat4 viewMatrix = glm::inverse(transform);

		return m_ProjectionMatrix * viewMatrix;
	}

	const Camera* Camera::GetMainCamera()
	{
		return m_MainCamera;
	}
}