#include "Debug.h"
#include "../Logger/Logger.h"

namespace Architect
{
	void Debug::Log(const std::string& message)
	{
		ARC_INFO(message);
	}

	void Debug::Log(const const char* message)
	{
		ARC_INFO(message);
	}

	void Debug::Warning(const std::string& message)
	{
		ARC_WARNING(message);
	}
	
	void Debug::Warning(const char* message)
	{
		ARC_WARNING(message);
	}

	void Debug::Error(const std::string& message)
	{
		ARC_ERROR(message);
	}

	void Debug::Error(const char* message)
	{
		ARC_ERROR(message);
	}
}