#pragma once

#include <memory>
#include "Logger/Logger.h"

#define ASSERT(x) if(!(x)) __debugbreak();

#define ASSERT_EXIT(x, message)\
{\
	if(!(x))\
	{\
		ARC_ENGINE_ERROR("Assertion Failed: Condition: {0}, Message: {1}", #x, message);\
		exit(EXIT_FAILURE);\
	}\
}

#define ASSERT_BREAK(x, message)\
{\
	if(!(x))\
	{\
		ARC_ENGINE_ERROR("Assertion Failed: Condition: {0}, Message: {1}", #x, message);\
		__debugbreak();\
	}\
}
	

namespace Architect
{
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using Scope = std::unique_ptr<T>;
}