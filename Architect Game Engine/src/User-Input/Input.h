#pragma once
#include "InputCodes.h"

namespace Architect
{
	class Input
	{
	public:
		static bool GetKeyDown(KeyCode keycode); // checks if a key has been pressed this frame

		static bool GetMouseButtonDown(MouseButtonCode mouseButtonCode);
	};

}

