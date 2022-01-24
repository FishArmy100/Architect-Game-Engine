#pragma once
#include "GUI/ImGuiWindow.h"
#include <memory>
#include <vector>
#include "Logger/Logger.h"

namespace Editor
{
	using namespace Architect;

	class EditorWindow : public UI::ImGuiWindow
	{
	public:
		EditorWindow(const std::string& title = "Window", ImGuiWindowFlags flags = 0);

		static void AddWindow(std::shared_ptr<EditorWindow> window);
		static void RemoveWindow(EditorWindow* window);
		static void ClearWindows();
		static void RenderWindows();
		static void UpdateWindows(float timestep);

		virtual ~EditorWindow() = default;

	public:
		static std::vector<std::shared_ptr<EditorWindow>> GetEditorWindows() { return m_EditorWindows; }

	protected:
		void OnWindowClosedAfterEvents() override final;

	private:
		static std::vector<std::shared_ptr<EditorWindow>> m_EditorWindows;
	};
}

