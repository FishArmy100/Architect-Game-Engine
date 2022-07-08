#include "Logger.h"

namespace Architect
{
	void Logger::Init()
	{
		std::string pattern = "%^[%T] %n: %v%$";
		spdlog::set_pattern(pattern);

		// Engine
		s_EngineLogger = spdlog::stdout_color_mt("[ARCHITECT]");
		s_EngineLogger->set_level(spdlog::level::trace);
		std::shared_ptr<SpdLogCallbackSink_mt> engineCallbackSink = std::make_shared<SpdLogCallbackSink_mt>(pattern);

		engineCallbackSink->GetLogEventHandler().AddLisener([&](const LogCallbackData data)
		{
			s_EngineLogEventHandler.Invoke(data);
		});

		s_EngineLogger->sinks().push_back(engineCallbackSink);

		// Client
		s_ClientLogger = spdlog::stdout_color_mt("[CLIENT]");
		s_ClientLogger->set_level(spdlog::level::trace);
		std::shared_ptr<SpdLogCallbackSink_mt> clientCallbackSink = std::make_shared<SpdLogCallbackSink_mt>(pattern);

		clientCallbackSink->GetLogEventHandler().AddLisener([&](const LogCallbackData data)
		{
			s_EngineLogEventHandler.Invoke(data);
		});

		s_ClientLogger->sinks().push_back(clientCallbackSink);

		s_IsInitialized = true;
	}

	std::shared_ptr<spdlog::logger> Logger::GetEngineLogger()
	{
		if (!s_IsInitialized)
			Init();

		return s_EngineLogger;
	}

	std::shared_ptr<spdlog::logger> Logger::GetClientLogger()
	{
		if (!s_IsInitialized)
			Init();

		return s_ClientLogger;
	}

	EventHandler<const LogCallbackData>& Logger::GetEngineLogEventHandler()
	{
		if (!s_IsInitialized)
			Init();

		return s_EngineLogEventHandler;
	}
	EventHandler<const LogCallbackData>& Logger::GetClientLogEventHandler()
	{
		if (!s_IsInitialized)
			Init();

		return s_ClientLogEventHandler;
	}
}