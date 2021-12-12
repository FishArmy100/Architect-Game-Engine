#pragma once
#include "GLFW/glfw3.h"

namespace Architect
{
	namespace UI
	{
		class GUI
		{
		private:
			static GLFWwindow* m_Window;

		public:
			static void Init(GLFWwindow* window);
			static void StartFrame();
			static void RenderFrame();
			static void ShutDown();
		};
	}
}

