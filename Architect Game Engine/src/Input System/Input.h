#pragma once

namespace Architect
{
	enum class KeyCode
	{
		A, B, C, D, E, F, G, H,
		I, J, K, L, M, N, O, P,
		Q, R, S, T, U, V, W, X,
		Y, Z,

		UpArrow, DownArrow,
		LeftArrow, RightArrow,

		LeftShift, RightShift,

		LeftContol, RightContol,

		LeftAlt, RightAlt,

		Space, Tab, CapsLock,

		Alfa1, Alfa2, Alfa3, Alfa4, Alfa5,
		Alfa6, Alfa7, Alfa8, Alfa9, Alfa0
	};

	enum class MouseButtonCode
	{
		Left,
		Right,
		Middle
	};

	class Input
	{
	public:
		static bool GetKey(KeyCode keycode); // checks if a key is being pressed
		static bool GetKeyDown(KeyCode keycode); // checks if a key has been pressed this frame
		static bool GetKeyUp(KeyCode keycode); // checks if a key has been releced

		static bool GetMouseButton(MouseButtonCode buttonCode); // checks if a mouse button is being pressed
		static bool GetMouseButtonDown(MouseButtonCode buttonCode); // checks if a mouse button has been pressed this frame
		static bool GetMouseButtonUp(MouseButtonCode buttonCode); // checks if a mouse button has been releced

		static float GetMouseScrollWheelDelta();
	};

}

