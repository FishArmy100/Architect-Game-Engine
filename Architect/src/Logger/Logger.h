#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "Core/Events.h"
#include "SpdLogCallbackSink.h"

namespace Architect
{
	class Logger
	{
	public:
		static std::shared_ptr<spdlog::logger> GetEngineLogger();
		static std::shared_ptr<spdlog::logger> GetClientLogger();

		static EventHandler<const LogCallbackData>& GetEngineLogEventHandler();
		static EventHandler<const LogCallbackData>& GetClientLogEventHandler();

	private:
		static void Init();

	private:
		static inline std::shared_ptr<spdlog::logger> s_EngineLogger = nullptr;
		static inline  std::shared_ptr<spdlog::logger> s_ClientLogger = nullptr;

		static inline EventHandler<const LogCallbackData> s_EngineLogEventHandler;
		static inline EventHandler<const LogCallbackData> s_ClientLogEventHandler;

		static inline bool s_IsInitialized = false;
	};
}

// engine logging
#define ARC_ENGINE_ERROR(...) ::Architect::Logger::GetEngineLogger()->error(__VA_ARGS__)
#define ARC_ENGINE_WARNING(...) ::Architect::Logger::GetEngineLogger()->warn(__VA_ARGS__)
#define ARC_ENGINE_INFO(...) ::Architect::Logger::GetEngineLogger()->info(__VA_ARGS__)
#define ARC_ENGINE_TRACE(...) ::Architect::Logger::GetEngineLogger()->trace(__VA_ARGS__)

// client logging
#define ARC_ERROR(...) ::Architect::Logger::GetClientLogger()->error(__VA_ARGS__)
#define ARC_WARNING(...) ::Architect::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define ARC_INFO(...) ::Architect::Logger::GetClientLogger()->info(__VA_ARGS__)
#define ARC_TRACE(...) ::Architect::Logger::GetClientLogger()->trace(__VA_ARGS__)

