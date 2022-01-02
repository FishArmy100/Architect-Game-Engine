#include "Input.h"
#include "GLFWInputUtils.h"
#include "Core.h"

namespace Architect
{
	std::shared_ptr<Input> Input::s_Instance;

	void Input::Init(Window* window)
	{
		ASSERT(s_Instance == nullptr);

		if (s_Instance == nullptr)
			s_Instance = std::make_shared<Input>(window);
	}

	bool Input::GetKeyDown(KeyCode keycode)
	{
		int key = GLFWInputUtils::ConvertKeyCodeToGLFWKeyCode(keycode);
		if (s_Instance->m_Keys.count(key) > 0)
		{
			KeyData data = s_Instance->m_Keys[key];
			return data.WasPressedThisFrame == true && data.WasPressedLastFrame == false;
		}

		return false;
	}

	bool Input::GetKeyUp(KeyCode keycode)
	{
		int key = GLFWInputUtils::ConvertKeyCodeToGLFWKeyCode(keycode);
		if (s_Instance->m_Keys.count(key) > 0)
		{
			KeyData data = s_Instance->m_Keys[key];
			return data.WasPressedThisFrame == false && data.WasPressedLastFrame == true;
		}

		return false;
	}

	bool Input::GetKey(KeyCode keycode)
	{
		int key = GLFWInputUtils::ConvertKeyCodeToGLFWKeyCode(keycode);
		if (s_Instance->m_Keys.count(key) > 0)
		{
			KeyData data = s_Instance->m_Keys[key];
			return data.WasPressedThisFrame == true;
		}

		return false;
	}

	bool Input::GetMouseButtonDown(MouseButtonCode mouseButtonCode)
	{
		int key = GLFWInputUtils::ConvertMouseButtonCodeToGLFWMouseButtonCode(mouseButtonCode);
		if (s_Instance->m_Buttons.count(key) > 0)
		{
			ButtonData data = s_Instance->m_Buttons[key];
			return data.WasPressedThisFrame == true && data.WasPressedLastFrame == false;
		}

		return false;
	}

	bool Input::GetMouseButtonUp(MouseButtonCode mouseButtonCode)
	{
		int key = GLFWInputUtils::ConvertMouseButtonCodeToGLFWMouseButtonCode(mouseButtonCode);
		if (s_Instance->m_Buttons.count(key) > 0)
		{
			ButtonData data = s_Instance->m_Buttons[key];
			return data.WasPressedThisFrame == false && data.WasPressedLastFrame == true;
		}

		return false;
	}

	bool Input::GetMouseButton(MouseButtonCode mouseButtonCode)
	{
		int key = GLFWInputUtils::ConvertMouseButtonCodeToGLFWMouseButtonCode(mouseButtonCode);
		if (s_Instance->m_Buttons.count(key) > 0)
		{
			ButtonData data = s_Instance->m_Buttons[key];
			return data.WasPressedThisFrame == true;
		}

		return false;
	}

	glm::vec2 Input::GetMousePosition()
	{
		GLFWwindow* window = s_Instance->m_Window->GetRawWindow();
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return glm::vec2((float)xPos, (float)yPos);
	}

	float Input::GetMouseScrollDelta()
	{
		return s_Instance->m_MouseScrollDelta;
	}

	Input::Input(Window* window) : m_MouseScrollDelta(0)
	{
		window->GetWindowEventHandler().AddLisener(&Input::OnWindowEvent, this);
		window->GetWindowUpdateEventHandler().AddLisener(&Input::OnWindowUpdate, this);
		m_Window = window;
	}

	void Input::OnWindowEvent(IWindowEvent* windowEvent)
	{
		if (KeyPressedEvent* eventData = dynamic_cast<KeyPressedEvent*>(windowEvent))
		{
			m_PressedKeys.push_back(eventData->Key);
		}

		if (KeyRelesedEvent* eventData = dynamic_cast<KeyRelesedEvent*>(windowEvent))
		{
			m_ReleasedKeys.push_back(eventData->Key);
		}

		if (MouseButtonPressedEvent* eventData = dynamic_cast<MouseButtonPressedEvent*>(windowEvent))
		{
			m_PressedButtons.push_back(eventData->Button);
		}

		if (MouseButtonReleasedEvent* eventData = dynamic_cast<MouseButtonReleasedEvent*>(windowEvent))
		{
			m_ReleasedButtons.push_back(eventData->Button);
		}

		if (MouseScrollEvent* eventData = dynamic_cast<MouseScrollEvent*>(windowEvent))
		{
			m_NextScrollDelta = eventData->YOffset;
		}
	}

	void Input::OnWindowUpdate()
	{
		// Keys
		for (auto&[key, data] : m_Keys)
		{
			data.WasPressedLastFrame = data.WasPressedThisFrame;
		}

		for (int key : m_PressedKeys)
		{
			m_Keys[key].WasPressedThisFrame = true;
		}

		for (int key : m_ReleasedKeys)
		{
			m_Keys[key].WasPressedThisFrame = false;

			auto it = std::find(m_PressedKeys.begin(), m_PressedKeys.end(), key);
			if (it != m_PressedKeys.end())
				m_PressedKeys.erase(it);
		}

		m_ReleasedKeys.clear();

		// Buttons
		for (auto& [key, data] : m_Buttons)
		{
			data.WasPressedLastFrame = data.WasPressedThisFrame;
		}

		for (int key : m_PressedButtons)
		{
			m_Buttons[key].WasPressedThisFrame = true;
		}

		for (int key : m_ReleasedButtons)
		{
			m_Buttons[key].WasPressedThisFrame = false;

			auto it = std::find(m_PressedButtons.begin(), m_PressedButtons.end(), key);
			if (it != m_PressedButtons.end())
				m_PressedButtons.erase(it);
		}

		m_ReleasedButtons.clear();

		// Scrolling
		m_MouseScrollDelta = m_NextScrollDelta;
		m_NextScrollDelta = 0;
	}
}