#include "Camera.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "RefLib/Registration/HelperRegistrationMacros.h"
#include "RefLib/Registration/BasicSTDRegistration.h"
#include "Serialization/Serializeable.h"

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

REFLIB_REGISTRATION
{
	REFLIB_BEGIN_CLASS(Architect::Camera)
		REFLIB_CTOR(float, float)
		REFLIB_CTOR(const Architect::Camera&)
		REFLIB_PROP_ACCESS(m_AspectRatio, AccessLevel::Private)
		REFLIB_PROP_ACCESS(m_Scale, AccessLevel::Private)
		REFLIB_ATTRIBUTE(Architect::Serializable([]() -> RefLib::Variant { return Architect::Camera(0,0); }))
	REFLIB_END_CLASS()
}