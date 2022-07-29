#pragma once
#include <type_traits>

namespace RefLib
{
	template<typename T>
	struct TypeRegistrationFactory : std::false_type
	{
		TypeRegistrationFactory() = default;
		//void operator()(); implemented in specialized type registration factories
	};
}