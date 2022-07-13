#pragma once
#include "Core/CorePrerequisites.h"
#include "Logger/Logger.h"

#ifdef ARC_DEBUG_BUILD
	#define ARC_ASSERT(x, message)\
	{\
		if(!(x))\
		{\
			std::string mes =std::string("File: " __FILE__ ", Line: ") + std::to_string(__LINE__) + "\n" + std::string(message);\
			Architect::Logger::GetClientLogger()->error(mes);\
			__debugbreak();\
		}\
	}
#else
	#define ARC_ASSERT(x, message)\
	{\
		if(!(x))\
		{\
			exit(EXIT_FAILURE);\
		}\
	}
#endif // ARC_DEBUG_BUILD
