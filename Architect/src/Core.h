#pragma once

#include <memory>
#include "Logger/Logger.h"
#include "RefLib/Utils/Ref.h"

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

#define ARC_THROW(ExeptionType, what) throw ExeptionType((std::string("Line: ") + std::to_string(__LINE__) + std::string(", File: " __FILE__ "\n\tWhat: ") + std::string(what)).c_str())
	

namespace Architect
{
	template<typename T>
	using Shared = std::shared_ptr<T>;

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = RefLib::Ref<T>;
	
	template<typename T>
	using ConstRef = RefLib::Ref<const T>;

	template<typename T>
	class Func { static_assert("T must be a function"); };

	template<typename TRet, typename... TArgs>
	class Func<TRet(TArgs...)>
	{
	public:
		Func(TRet(*func)(TArgs...)) : m_Func(func) {}

		template<typename TFunc>
		Func(TFunc func) : m_Func(func) {}

		inline TRet operator()(TArgs... args) { return std::move(m_Func(std::forward<TArgs>(args)...)); }

	private:
		TRet(*m_Func)(TArgs...);
	};

	template<typename... TArgs>
	class Func<void(TArgs...)>
	{
	public:
		Func(void(*func)(TArgs...)) : m_Func(func) {}

		template<typename TFunc>
		Func(TFunc func) : m_Func(func) {}

		inline void operator()(TArgs... args) { m_Func(std::forward<TArgs>(args)...); }

	private:
		void(*m_Func)(TArgs...);
	};
}