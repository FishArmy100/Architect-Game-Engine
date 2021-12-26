#include "GLFWInputHandler.h"

namespace Architect
{
	GLFWInputHandler::GLFWInputHandler(GLFWwindow* window)
	{
		Window = window;
	}

	bool GLFWInputHandler::IsKeyDown(KeyCode keycode)
	{
		int code = ConvertKeyCodeToGLFWKeyCode(keycode);
		return glfwGetKey(Window, code) == GLFW_PRESS;
	}

	bool GLFWInputHandler::IsMouseButtonDown(MouseButtonCode mouseButtonCode)
	{
		int code = ConvertMouseButtonCodeToGLFWMouseCode(mouseButtonCode);
		return glfwGetMouseButton(Window, code) == GLFW_PRESS;
	}

	int GLFWInputHandler::ConvertMouseButtonCodeToGLFWMouseCode(MouseButtonCode mouseButtonCode)
	{
		switch (mouseButtonCode)
		{
		case MouseButtonCode::Left:
			return GLFW_MOUSE_BUTTON_1;
		case MouseButtonCode::Right:
			GLFW_MOUSE_BUTTON_2;
		case MouseButtonCode::Middle:
			GLFW_MOUSE_BUTTON_3;
		default:
			break;
		}
	}

	int GLFWInputHandler::ConvertKeyCodeToGLFWKeyCode(KeyCode keycode)
	{
		switch (keycode)
		{
		case KeyCode::A:
			return GLFW_KEY_A;
		case KeyCode::B:
			return GLFW_KEY_B;
		case KeyCode::C:
			return GLFW_KEY_C;
		case KeyCode::D:
			return GLFW_KEY_D;
		case KeyCode::E:
			return GLFW_KEY_E;
		case KeyCode::F:
			return GLFW_KEY_F;
		case KeyCode::G:
			return GLFW_KEY_G;
		case KeyCode::H:
			return GLFW_KEY_H;
		case KeyCode::I:
			return GLFW_KEY_I;
		case KeyCode::J:
			return GLFW_KEY_J;
		case KeyCode::K:
			return GLFW_KEY_K;
		case KeyCode::L:
			return GLFW_KEY_L;
		case KeyCode::M:
			return GLFW_KEY_M;
		case KeyCode::N:
			return GLFW_KEY_N;
		case KeyCode::O:
			return GLFW_KEY_O;
		case KeyCode::P:
			return GLFW_KEY_P;
		case KeyCode::Q:
			return GLFW_KEY_Q;
		case KeyCode::R:
			return GLFW_KEY_R;
		case KeyCode::S:
			return GLFW_KEY_S;
		case KeyCode::T:
			return GLFW_KEY_T;
		case KeyCode::U:
			return GLFW_KEY_U;
		case KeyCode::V:
			return GLFW_KEY_V;
		case KeyCode::W:
			return GLFW_KEY_W;
		case KeyCode::X:
			return GLFW_KEY_X;
		case KeyCode::Y:
			return GLFW_KEY_Y;
		case KeyCode::Z:
			return GLFW_KEY_Z;
		case KeyCode::UpArrow:
			return GLFW_KEY_UP;
		case KeyCode::DownArrow:
			return GLFW_KEY_DOWN;
		case KeyCode::LeftArrow:
			return GLFW_KEY_LEFT;
		case KeyCode::RightArrow:
			return GLFW_KEY_RIGHT;
		case KeyCode::LeftShift:
			return GLFW_KEY_LEFT_SHIFT;
		case KeyCode::RightShift:
			return GLFW_KEY_RIGHT_SHIFT;
		case KeyCode::LeftContol:
			return GLFW_KEY_LEFT_CONTROL;
		case KeyCode::RightContol:
			return GLFW_KEY_RIGHT_CONTROL;
		case KeyCode::LeftAlt:
			return GLFW_KEY_LEFT_ALT;
		case KeyCode::RightAlt:
			return GLFW_KEY_RIGHT_ALT;
		case KeyCode::Space:
			return GLFW_KEY_SPACE;
		case KeyCode::Tab:
			return GLFW_KEY_TAB;
		case KeyCode::CapsLock:
			return GLFW_KEY_CAPS_LOCK;
		case KeyCode::Alfa1:
			return GLFW_KEY_1;
		case KeyCode::Alfa2:
			return GLFW_KEY_2;
		case KeyCode::Alfa3:
			return GLFW_KEY_3;
		case KeyCode::Alfa4:
			return GLFW_KEY_4;
		case KeyCode::Alfa5:
			return GLFW_KEY_5;
		case KeyCode::Alfa6:
			return GLFW_KEY_6;
		case KeyCode::Alfa7:
			return GLFW_KEY_7;
		case KeyCode::Alfa8:
			return GLFW_KEY_8;
		case KeyCode::Alfa9:
			return GLFW_KEY_9;
		case KeyCode::Alfa0:
			return GLFW_KEY_0;
		default:
			break;
		}

		return 0;
	}
}