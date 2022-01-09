#include "ConsoleWindow.h"

namespace Editor
{
	using namespace Architect;

	ConsoleWindow::ConsoleWindow() : EditorWindow("Console Window", 0)
	{
		m_ClientLisener = Logger::GetClientLogEventHandler().AddLisener([&](const LogCallbackData data)
		{
			m_ConsoleLogs.emplace_back(data.Message);
		});

		m_EngineLisener = Logger::GetEngineLogEventHandler().AddLisener([&](const LogCallbackData data)
		{
			m_ConsoleLogs.emplace_back(data.Message);
		});
	}

	ConsoleWindow::~ConsoleWindow()
	{
		m_ClientLisener->Detach();
		m_EngineLisener->Detach();
	}

	void ConsoleWindow::OnRenderWindow(float timestep)
	{
		ImGui::BeginChild("Scrollable Reigon");
		for (int i = m_ConsoleLogs.size() - 1; i >= 0; i--)
		{
			ImGui::Text(m_ConsoleLogs[i].c_str());
		}
		ImGui::EndChild();
	}
}