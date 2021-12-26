#pragma once
#include "InputCodes.h"
#include "IInputHandler.h"
#include <GLFW/glfw3.h>
#include <memory>

namespace Architect
{
	class InputSystem
	{
	public:
		static bool IsKeyDown(KeyCode keycode);
		static bool IsMouseButtonDown(MouseButtonCode mouseButtonCode);
		static void Init(std::shared_ptr<IInputHandler> inputHandler);

	private:
		static std::shared_ptr<IInputHandler> InputHandler;
	};
}

