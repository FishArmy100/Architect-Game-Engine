#pragma once
#include "glm/mat4x4.hpp"
#include "RefLib/Registration/RegistrationFriend.h"

namespace Architect
{
	class Camera
	{
	public:
		Camera(float aspectRatio, float scale);
		glm::mat4 GetProjectionMatrix() const;

		void SetAspectRatio(float aspectRatio);
		float GetAspectRatio() const { return m_AspectRatio; }

		void SetScale(float scale);
		float GetScale() const { return m_Scale; }

	private:
		float m_AspectRatio;
		float m_Scale;
		REFLIB_FRIEND
	};
}

