#include "Input.h"
#include "raylib.h"

namespace Architect
{
	int ConvertMouseButtonCodeToRaylibButtonID(MouseButtonCode mouseButtonCode)
	{
		switch (mouseButtonCode)
		{
		case MouseButtonCode::Left:
			return MOUSE_BUTTON_LEFT;
		case MouseButtonCode::Right:
			return MOUSE_BUTTON_RIGHT;
		case MouseButtonCode::Middle:
			return MOUSE_BUTTON_MIDDLE;
		default:
			return -1;
		}
	}

	bool Input::GetMouseButton(MouseButtonCode mouseButton)
	{
		int buttonId = ConvertMouseButtonCodeToRaylibButtonID(mouseButton);
		return IsMouseButtonDown(buttonId);
	}

	bool Input::GetMouseButtonDown(MouseButtonCode mouseButton)
	{
		int buttonId = ConvertMouseButtonCodeToRaylibButtonID(mouseButton);
		return IsMouseButtonPressed(buttonId);
	}

	bool Input::GetMouseButtonUp(MouseButtonCode mouseButton)
	{
		int buttonId = ConvertMouseButtonCodeToRaylibButtonID(mouseButton);
		return IsMouseButtonReleased(buttonId);
	}

	int ConvertKeyCodeToRaylibKeyID(KeyCode keycode);

	bool Input::GetKey(KeyCode keycode)
	{
		int keyId = ConvertKeyCodeToRaylibKeyID(keycode);
		return IsKeyDown(keyId);
	}

	bool Input::GetKeyDown(KeyCode keycode)
	{
		int keyId = ConvertKeyCodeToRaylibKeyID(keycode);
		return IsKeyPressed(keyId);
	}

	bool Input::GetKeyUp(KeyCode keycode)
	{
		int keyId = ConvertKeyCodeToRaylibKeyID(keycode);
		return IsKeyReleased(keyId);
	}

	float Input::GetMouseScrollWheelDelta()
	{
		return GetMouseWheelMove();
	}

	int ConvertKeyCodeToRaylibKeyID(KeyCode keycode)
	{
		switch (keycode)
		{
		case KeyCode::A:
			return KEY_A;
		case KeyCode::B:
			return KEY_B;
		case KeyCode::C:
			return KEY_C;
		case KeyCode::D:
			return KEY_D;
		case KeyCode::E:
			return KEY_E;
		case KeyCode::F:
			return KEY_F;
		case KeyCode::G:
			return KEY_G;
		case KeyCode::H:
			return KEY_H;
		case KeyCode::I:
			return KEY_I;
		case KeyCode::J:
			return KEY_J;
		case KeyCode::K:
			return KEY_K;
		case KeyCode::L:
			return KEY_L;
		case KeyCode::M:
			return KEY_M;
		case KeyCode::N:
			return KEY_N;
		case KeyCode::O:
			return KEY_O;
		case KeyCode::P:
			return KEY_P;
		case KeyCode::Q:
			return KEY_Q;
		case KeyCode::R:
			return KEY_R;
		case KeyCode::S:
			return KEY_S;
		case KeyCode::T:
			return KEY_T;
		case KeyCode::U:
			return KEY_U;
		case KeyCode::V:
			return KEY_V;
		case KeyCode::W:
			return KEY_W;
		case KeyCode::X:
			return KEY_X;
		case KeyCode::Y:
			return KEY_Y;
		case KeyCode::Z:
			return KEY_Z;

		case KeyCode::UpArrow:
			return KEY_UP;
		case KeyCode::DownArrow:
			return KEY_DOWN;
		case KeyCode::RightArrow:
			return KEY_RIGHT;
		case KeyCode::LeftArrow:
			return KEY_LEFT;

		case KeyCode::LeftShift:
			return KEY_LEFT_SHIFT;
		case KeyCode::RightShift:
			return KEY_RIGHT_SHIFT;

		case KeyCode::LeftContol:
			return KEY_LEFT_CONTROL;
		case KeyCode::RightContol:
			return KEY_RIGHT_CONTROL;

		case KeyCode::LeftAlt:
			return KEY_LEFT_ALT;
		case KeyCode::RightAlt:
			return KEY_RIGHT_ALT;

		case KeyCode::Space:
			return KEY_SPACE;
		case KeyCode::Tab:
			return KEY_TAB;
		case KeyCode::CapsLock:
			return KEY_CAPS_LOCK;

		case KeyCode::Alfa1:
			return KEY_ONE;
		case KeyCode::Alfa2:
			return KEY_TWO;
		case KeyCode::Alfa3:
			return KEY_THREE;
		case KeyCode::Alfa4:
			return KEY_FOUR;
		case KeyCode::Alfa5:
			return KEY_FIVE;
		case KeyCode::Alfa6:
			return KEY_SIX;
		case KeyCode::Alfa7:
			return KEY_SEVEN;
		case KeyCode::Alfa8:
			return KEY_EIGHT;
		case KeyCode::Alfa9:
			return KEY_NINE;
		case KeyCode::Alfa0:
			return KEY_ZERO;
		}

		return KEY_ZERO;
	}
}