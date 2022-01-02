#pragma once
#include "InputCodes.h"
#include "glm/vec2.hpp"
#include <memory>
#include <vector>
#include "Core/Window.h"
#include <map>

namespace Architect
{
	class Input
	{
	public:
		static void Init(Window* window);

		static bool GetKeyDown(KeyCode keycode);
		static bool GetKeyUp(KeyCode keycode);
		static bool GetKey(KeyCode keycode);

		static bool GetMouseButtonDown(MouseButtonCode mouseButtonCode);
		static bool GetMouseButtonUp(MouseButtonCode mouseButtonCode);
		static bool GetMouseButton(MouseButtonCode mouseButtonCode);

		static glm::vec2 GetMousePosition();
		static float GetMouseScrollDelta();

	public:
		Input(Window* window);
		void OnWindowEvent(IWindowEvent* windowEvent);
		void OnWindowUpdate();

	private:
		static std::shared_ptr<Input> s_Instance;

		struct KeyData
		{
			bool WasPressedThisFrame = false;
			bool WasPressedLastFrame = false;
		};

		struct ButtonData
		{
			bool WasPressedThisFrame = false;
			bool WasPressedLastFrame = false;
		};

		std::map<int, KeyData> m_Keys;
		std::vector<int> m_PressedKeys;
		std::vector<int> m_ReleasedKeys;

		std::map<int, ButtonData> m_Buttons;
		std::vector<int> m_PressedButtons;
		std::vector<int> m_ReleasedButtons;

		float m_NextScrollDelta = 0;
		float m_MouseScrollDelta = 0;

		Window* m_Window;
	};

}

