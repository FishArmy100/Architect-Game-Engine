#include "EditorCamera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "User-Input/Input.h"

namespace Editor
{
	using namespace Architect;

	EditorCamera::EditorCamera(glm::vec2 startPosition, float panSpeed, float zoomSpeed, float startZoom)
		: m_CameraPos(startPosition), m_CurrentZoom(startZoom), m_PreviousMousePos(glm::vec2(0)), 
		m_ZoomSpeed(zoomSpeed), m_PanSpeed(panSpeed), m_Camera(std::make_shared<Camera>(0, 2))
	{
	}

	void EditorCamera::Update(float deltaTime, glm::vec2 mousePos)
	{
		if (Input::GetMouseButton(MouseButtonCode::Right))
		{
			glm::vec2 direction = mousePos - m_PreviousMousePos;
			m_CameraPos -= direction * m_PanSpeed * deltaTime;
		}

		m_CurrentZoom -= Input::GetMouseScrollDelta() * m_ZoomSpeed * deltaTime;

		m_Camera->SetScale(m_CurrentZoom);

		m_PreviousMousePos = mousePos;
	}

	void EditorCamera::SetAspectRatio(float aspectRatio)
	{
		m_Camera->SetAspectRatio(aspectRatio);
	}

	glm::mat4 EditorCamera::GetTransformMatrix()
	{
		return glm::translate(glm::mat4(1.0f), { m_CameraPos.x, m_CameraPos.y, 0.0f});
	}
}