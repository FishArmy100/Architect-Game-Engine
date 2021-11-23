#include "Debug.h"
#include "../Logger/Logger.h"

namespace Architect
{
	void Debug::Log(std::string& message)
	{
		ARC_INFO(message);
	}

	void Debug::Log(const char* message)
	{
		ARC_INFO(message);
	}

	void Debug::Warning(std::string& message)
	{
		ARC_WARNING(message);
	}
	
	void Debug::Warning(const char* message)
	{
		ARC_WARNING(message);
	}

	void Debug::Error(std::string& message)
	{
		ARC_ERROR(message);
	}

	void Debug::Error(const char* message)
	{
		ARC_ERROR(message);
	}
}