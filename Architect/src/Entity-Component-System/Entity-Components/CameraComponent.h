#pragma once
#include "Rendering-System/Camera.h"
#include "Reflection/RegistrationMacros.h"

namespace Architect
{
	struct CameraComponent
	{
		CameraComponent(Camera camera) : Camera(camera) {}
		CameraComponent(const CameraComponent&) = default;
		~CameraComponent() = default;

		Camera Camera;
	};
}

ARC_REFLECT_AUTO(Architect::CameraComponent)