#pragma once
#include "IApplicationEvent.h"
#include <sstream>

namespace Architect
{
	struct IWindowEvent : public IApplicationEvent
	{
		virtual ~IWindowEvent() {}
	};

	struct WindowResizeEvent : public IWindowEvent
	{
		WindowResizeEvent(int width, int height) : Width(width), Height(height) {}

		std::string GetDebugString() override
		{
			std::stringstream ss;
			ss << "Window Resize Event: Width: " << Width << ", Height: " << Height;
			return ss.str();
		}

		int Width;
		int Height;
	};

	struct WindowTitleRenamedEvent: public IWindowEvent
	{
		WindowTitleRenamedEvent(const std::string& newTitle) : NewTitle(newTitle) {}

		std::string GetDebugString() override
		{
			std::stringstream ss;
			ss << "Window Renamed Event: Title: " << NewTitle;
			return ss.str();
		}

		std::string NewTitle;
	};

	struct WindowCloseEvent : public IWindowEvent
	{
		WindowCloseEvent() {}
		std::string GetDebugString() override
		{
			return std::string("Window Closed Event"); 
		}
	};

	struct KeyPressedEvent : public IWindowEvent
	{
		KeyPressedEvent(int key, int scanCode, int mods) : Key(key), ScanCode(scanCode), Mods(mods) {}

		std::string GetDebugString() override
		{
			std::stringstream ss;
			ss << "Key Pressed Event: Key: " << Key;
			return ss.str();
		}

		int Key;
		int ScanCode;
		int Mods;
	};

	struct KeyRelesedEvent : public IWindowEvent
	{
		KeyRelesedEvent(int key, int scanCode, int mods) : Key(key), ScanCode(scanCode), Mods(mods) {}

		std::string GetDebugString() override
		{
			std::stringstream ss;
			ss << "Key Relesed Event: Key: " << Key;
			return ss.str();
		}

		int Key;
		int ScanCode;
		int Mods;
	};

	struct KeyRepeatEvent : public IWindowEvent
	{
		KeyRepeatEvent(int key, int scanCode, int mods) : Key(key), ScanCode(scanCode), Mods(mods) {}

		std::string GetDebugString() override
		{
			std::stringstream ss;
			ss << "Key Repeat Event: Key: " << Key;
			return ss.str();
		}

		int Key;
		int ScanCode;
		int Mods;
	};

	struct MouseButtonPressedEvent : public IWindowEvent
	{
		MouseButtonPressedEvent(int button, int mods) : Button(button), Mods(mods) {}

		std::string GetDebugString() override
		{
			std::stringstream ss;
			ss << "Mouse Button Pressed Event: Button: " << Button;
			return ss.str();
		}

		int Button;
		int Mods;
	};

	struct MouseButtonReleasedEvent : public IWindowEvent
	{
		MouseButtonReleasedEvent(int button, int mods) : Button(button), Mods(mods) {}

		std::string GetDebugString() override
		{
			std::stringstream ss;
			ss << "Mouse Button Released Event: Button: " << Button;
			return ss.str();
		}

		int Button;
		int Mods;
	};

	struct MouseScrollEvent : public IWindowEvent
	{
		MouseScrollEvent(float xOffset, float yOffset) : XOffset(xOffset), YOffset(yOffset) {}

		std::string GetDebugString() override
		{
			std::stringstream ss;
			ss << "Mouse Scroll Event: X Offset: " << XOffset << ", Y Offset: " << YOffset;
			return ss.str();
		}

		float XOffset;
		float YOffset;
	};

	struct MouseMovedEvent : public IWindowEvent
	{
		MouseMovedEvent(float xPos, float yPos) : XPos(xPos), YPos(yPos) {}

		std::string GetDebugString() override
		{
			std::stringstream ss;
			ss << "Mouse Moved Event: X Position: " << XPos << ", Y Position: " << YPos;
			return ss.str();
		}

		float XPos;
		float YPos;
	};
}