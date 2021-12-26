#pragma once
#include "Rendering-System/Camera.h"

namespace Architect
{
	struct CameraComponent
	{
		CameraComponent(Camera* camera) : Camera(camera) { }
		~CameraComponent(){}

		Camera* Camera;
	};
}