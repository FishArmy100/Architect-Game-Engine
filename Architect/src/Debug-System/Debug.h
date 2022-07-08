#pragma once
#include <string>

namespace Architect
{
	class Debug
	{
	public:
		static void Log(const std::string& message);
		static void Log(const char* message);

		static void Warning(const std::string& message);
		static void Warning(const char* message);

		static void Error(const std::string& message);
		static void Error(const char* message);
	};
}

