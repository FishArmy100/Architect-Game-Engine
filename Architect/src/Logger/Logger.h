#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Architect
{
	class Logger
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return engineLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> engineLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
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

