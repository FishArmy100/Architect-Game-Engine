#pragma once
#include <string>

namespace Architect
{
	class Debug
	{
	public:
		static void Log(std::string& message);
		static void Log(const char* message);

		static void Warning(std::string& message);
		static void Warning(const char* message);

		static void Error(std::string& message);
		static void Error(const char* message);
	};
}

