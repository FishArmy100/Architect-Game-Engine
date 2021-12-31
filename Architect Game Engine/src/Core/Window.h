#pragma once
#include "IApplicationEvent.h"
#include "Events.h"
#include <string>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <memory>
#include "WindowEvents.h"

namespace Architect
{
	class Window
	{
	public:
		static Window* Create(unsigned int width, unsigned int height, const std::string& title = "Architect Application");
		~Window();

		void Update();
		void Clear();
		void SetTitle(const std::string& title);
		unsigned int GetWidth() { return m_WindowData.Width; }
		unsigned int GetHeight() { return m_WindowData.Height; }
		GLFWwindow* GetRawWindow() { return m_Window; }

		EventHandler<IWindowEvent*>& GetWindowEventHandler() { return m_WindowEventHandler; };
		EventHandler<void>& GetWindowUpdateEventHandler() { return m_WindowUpdateEventHandler; }

	private:
		Window(GLFWwindow* window, const std::string& title);
		static GLFWwindow* CreateGLFWWindow(unsigned int width, unsigned int height, const std::string& title);
		void InitilizeWindowEvents(GLFWwindow* window);

	private:
		struct WindowData
		{
			WindowData() : Width(0), Height(0), Title(""), OnWindowEvent(nullptr) {}

			WindowData(unsigned int width, unsigned int height, const std::string& title, std::function<void(IWindowEvent*, std::function<void(IWindowEvent*)>)> onWindowEvent)
				: Width(width), Height(height), Title(title), OnWindowEvent(onWindowEvent) {}

			unsigned int Width;
			unsigned int Height;
			std::string Title;
			std::function<void(IWindowEvent*, std::function<void(IWindowEvent*)>)> OnWindowEvent;
		};

		static bool s_GLFWInitialized;

		EventHandler<IWindowEvent*> m_WindowEventHandler;
		EventHandler<void> m_WindowUpdateEventHandler;
		GLFWwindow* m_Window;
		WindowData m_WindowData;
	};
}

