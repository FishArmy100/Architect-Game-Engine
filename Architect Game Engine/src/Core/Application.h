#pragma once
#include "LayerStack.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GUI/ImGuiLayer.h"

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
		GLFWwindow* GetWindow() { return m_Window; }

		void Run();

	private:
		bool InitializeOpenGL(GLFWwindow*& window);
		void ShutDownOpenGL();
		void InitalizeInputSystem(GLFWwindow* window);

		void OnSceneChanged();

	private:
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
		GLFWwindow* m_Window;
		ImGuiLayer* m_ImGuiLayer;

	private:
		static Application* s_Instance;

	};
}

