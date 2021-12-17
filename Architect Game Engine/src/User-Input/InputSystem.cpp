#include "InputSystem.h"

namespace Architect
{
	std::shared_ptr<IInputHandler> InputSystem::InputHandler;


	bool InputSystem::IsKeyDown(KeyCode keycode)
	{
		return InputHandler->IsKeyDown(keycode);
	}

	bool InputSystem::IsMouseButtonDown(MouseButtonCode mouseButtonCode)
	{
		return InputHandler->IsMouseButtonDown(mouseButtonCode);
	}

	void InputSystem::Init(std::shared_ptr<IInputHandler> inputHandler)
	{
		InputHandler = inputHandler;
	}
}
