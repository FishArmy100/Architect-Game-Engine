#include "Camera.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Architect
{
	Camera::Camera(float aspectRatio, float scale)
		: m_AspectRatio(aspectRatio), m_Scale(scale)
	{
	}

	glm::mat4 Camera::GetProjectionMatrix() const
	{
		return glm::ortho(-m_AspectRatio * m_Scale, m_AspectRatio * m_Scale, -m_Scale, m_Scale);
	}

	void Camera::SetAspectRatio(float aspectRatio)
	{
		m_AspectRatio = aspectRatio;
	}

	void Camera::SetScale(float scale)
	{
		m_Scale = scale;
	}
}