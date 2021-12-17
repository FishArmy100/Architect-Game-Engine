#pragma once
#include "IInputHandler.h"
#include "GLFW/glfw3.h"

namespace Architect
{
	class GLFWInputHandler : public IInputHandler
	{
	public:
		GLFWInputHandler(GLFWwindow* window);
		bool IsKeyDown(KeyCode keycode) override;
		bool IsMouseButtonDown(MouseButtonCode mouseButtonCode) override;

	private:
		int ConvertKeyCodeToGLFWKeyCode(KeyCode keycode);
		int ConvertMouseButtonCodeToGLFWMouseCode(MouseButtonCode mouseButtonCode);

		GLFWwindow* Window;
	};
}

