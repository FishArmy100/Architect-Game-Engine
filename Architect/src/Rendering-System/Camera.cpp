#include "Camera.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Architect
{
	Camera::Camera(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top);
	}
}