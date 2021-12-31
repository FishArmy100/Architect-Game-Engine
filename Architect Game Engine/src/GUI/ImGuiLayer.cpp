#include "ImGuiLayer.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Core/Application.h"
#include "../Core.h"

namespace Architect
{
	ImGuiLayer::ImGuiLayer() : Layer("ImGUI layer")
	{

	}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		GLFWwindow* window = Application::Get().GetWindow()->GetRawWindow();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 130");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	bool ImGuiLayer::OnEvent(IApplicationEvent* appEvent)
	{
		ImGuiIO& io = ImGui::GetIO();

		bool isKeyEvent = 
			dynamic_cast<KeyPressedEvent*>(appEvent) ||
			dynamic_cast<KeyRelesedEvent*>(appEvent) ||
			dynamic_cast<KeyRepeatEvent*>(appEvent);

		bool isMouseButtonEvent =
			dynamic_cast<MouseButtonPressedEvent*>(appEvent) ||
			dynamic_cast<MouseButtonReleasedEvent*>(appEvent);

		bool blockedEvent = false;
		blockedEvent |= isKeyEvent & io.WantCaptureKeyboard;
		blockedEvent |= isMouseButtonEvent & io.WantCaptureMouse;

		return blockedEvent;
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGui::Render();
		Window* window2 = Application::Get().GetWindow();
		glViewport(0, 0, window2->GetWidth(), window2->GetHeight());
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}