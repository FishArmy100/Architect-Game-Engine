#pragma once
#include "LayerStack.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GUI/ImGuiLayer.h"
#include "Window.h"

namespace Architect
{
	class Application
	{
	public:
		Application(const std::string& name = "Architect App");
		virtual ~Application();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void Close();

		static Application& Get() { return *s_Instance; }
		Window* GetWindow() { return m_Window; }
		const std::string& GetName() { return m_ApplicationName; }

		void Run();

	private:
		void OnSceneChanged();
		void OnWindowEvent(IWindowEvent* windowEvent);
		void OnEvent(IApplicationEvent* appEvent);

	private:
		std::string m_ApplicationName;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
		Window* m_Window;
		ImGuiLayer* m_ImGuiLayer;

	private:
		static Application* s_Instance;

	};
}

