#include "Logger.h"

namespace Architect
{
	std::shared_ptr<spdlog::logger> Logger::engineLogger;
	std::shared_ptr<spdlog::logger> Logger::clientLogger;

	void Logger::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		engineLogger = spdlog::stdout_color_mt("[ARCHITECT]");
		engineLogger->set_level(spdlog::level::trace);

		clientLogger = spdlog::stdout_color_mt("[CLIENT]");
		clientLogger->set_level(spdlog::level::trace);
	}
}