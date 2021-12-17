#include "Input.h"
#include "InputSystem.h"

namespace Architect
{
	bool Input::GetKeyDown(KeyCode keycode)
	{
		return InputSystem::IsKeyDown(keycode);
	}

	bool Input::GetMouseButtonDown(MouseButtonCode mouseButtonCode)
	{
		return InputSystem::IsMouseButtonDown(mouseButtonCode);
	}
}