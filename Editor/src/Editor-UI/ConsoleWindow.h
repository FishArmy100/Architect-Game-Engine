#pragma once
#include "EditorWindow.h"
#include "Logger/Logger.h"

namespace Editor
{
	class ConsoleWindow : public EditorWindow
	{
	public:
		ConsoleWindow();
		~ConsoleWindow();

	protected:
		void OnRenderWindow(float timestep) override;

	private:
		std::shared_ptr<EventLisener<const LogCallbackData>> m_ClientLisener;
		std::shared_ptr<EventLisener<const LogCallbackData>> m_EngineLisener;
		std::vector<std::string> m_ConsoleLogs;
	};
}

