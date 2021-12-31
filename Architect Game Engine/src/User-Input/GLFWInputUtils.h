#pragma once
#include "InputCodes.h"

namespace Architect
{
	class GLFWInputUtils
	{
	public:
		static int ConvertKeyCodeToGLFWKeyCode(KeyCode keycode);
		static int ConvertMouseButtonCodeToGLFWMouseButtonCode(MouseButtonCode mouseButtonCode);
	};
}

