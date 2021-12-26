#pragma once
#include "InputCodes.h"

namespace Architect
{
	class IInputHandler
	{
	public:
		virtual bool IsKeyDown(KeyCode keycode) = 0;
		virtual bool IsMouseButtonDown(MouseButtonCode mouseButtonCode) = 0;
	};
}