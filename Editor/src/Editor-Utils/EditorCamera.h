#pragma once
#include "Rendering-System/Camera.h"
#include <memory>

namespace Editor
{
	class EditorCamera
	{
	public:
		EditorCamera(glm::vec2 startPosition, float panSpeed, float zoomSpeed, float startZoom);
		void Update(float deltaTime, glm::vec2 mousePos);

		void SetAspectRatio(float aspectRatio);
		Architect::Camera& GetCamera() { return m_Camera; }

		glm::mat4 GetTransformMatrix();

	private:
		glm::vec2 m_CameraPos;
		float m_CurrentZoom;
		glm::vec2 m_PreviousMousePos;

		float m_ZoomSpeed;
		float m_PanSpeed;

		Architect::Camera m_Camera;
	};
}
