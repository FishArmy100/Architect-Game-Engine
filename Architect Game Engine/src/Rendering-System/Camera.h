#pragma once
#include "glm/mat4x4.hpp"

namespace Architect
{
	class Camera
	{
	private:
		glm::mat4 m_ProjectionMatrix;

	public:
		Camera(float left, float right, float bottom, float top);
		glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
	};
}

