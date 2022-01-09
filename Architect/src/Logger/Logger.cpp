#include "Logger.h"

namespace Architect
{
	std::shared_ptr<spdlog::logger> Logger::m_EngineLogger;
	std::shared_ptr<spdlog::logger> Logger::m_ClientLogger;

	EventHandler<const LogCallbackData> Logger::m_EngineLogEventHandler;
	EventHandler<const LogCallbackData> Logger::m_ClientLogEventHandler;

	void Logger::Init()
	{
		std::string pattern = "%^[%T] %n: %v%$";
		spdlog::set_pattern(pattern);

		// Engine
		m_EngineLogger = spdlog::stdout_color_mt("[ARCHITECT]");
		m_EngineLogger->set_level(spdlog::level::trace);
		std::shared_ptr<SpdLogCallbackSink_mt> engineCallbackSink = std::make_shared<SpdLogCallbackSink_mt>(pattern);

		engineCallbackSink->GetLogEventHandler().AddLisener([&](const LogCallbackData data)
		{
			m_EngineLogEventHandler.Invoke(data);
		});

		m_EngineLogger->sinks().push_back(engineCallbackSink);

		// Client
		m_ClientLogger = spdlog::stdout_color_mt("[CLIENT]");
		m_ClientLogger->set_level(spdlog::level::trace);
		std::shared_ptr<SpdLogCallbackSink_mt> clientCallbackSink = std::make_shared<SpdLogCallbackSink_mt>(pattern);

		clientCallbackSink->GetLogEventHandler().AddLisener([&](const LogCallbackData data)
		{
			m_EngineLogEventHandler.Invoke(data);
		});

		m_ClientLogger->sinks().push_back(clientCallbackSink);
	}
}