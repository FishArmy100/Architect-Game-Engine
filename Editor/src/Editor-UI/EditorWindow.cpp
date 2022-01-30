#include "EditorWindow.h"

namespace Editor
{
	std::vector<std::shared_ptr<EditorWindow>> EditorWindow::m_EditorWindows;

	EditorWindow::EditorWindow(const std::string& title, ImGuiWindowFlags flags) : UI::ImGuiWindow(title, flags)
	{

	}

	void EditorWindow::AddWindow(std::shared_ptr<EditorWindow> window)
	{
		auto it = std::find(m_EditorWindows.begin(), m_EditorWindows.end(), window);
		if (it == m_EditorWindows.end())
		{
			m_EditorWindows.push_back(window);
		}
	}

	void EditorWindow::RemoveWindow(EditorWindow* window)
	{
		for (int i = 0; i < m_EditorWindows.size(); i++)
		{
			if (m_EditorWindows[i].get() == window)
			{
				auto it = m_EditorWindows.begin() + i;
				m_EditorWindows.erase(it);
				return;
			}
		}
	}

	void EditorWindow::ClearWindows()
	{
		m_EditorWindows.clear();
	}

	void EditorWindow::UpdateWindows(float timestep)
	{
		for (int i = 0; i < m_EditorWindows.size(); i++)
			m_EditorWindows[i]->UpdateWindow(timestep);
	}

	void EditorWindow::RenderWindows()
	{
		for (int i = 0; i < m_EditorWindows.size(); i++)
			m_EditorWindows[i]->RenderWindow();
	}

	void EditorWindow::OnWindowClosedAfterEvents()
	{
		RemoveWindow(this);
	}
}