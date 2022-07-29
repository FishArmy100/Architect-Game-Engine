#pragma once
#include <functional>
#include "RefLib/Variant/Variant.h"
#include "RefLib/Registration/TypeRegistrationFactory.h"
#include "Reflection/RegistrationMacros.h"

namespace Architect
{
	struct Serializable 
	{
		Serializable(std::optional<std::function<RefLib::Variant()>> defaultCtor) : DefaultConstructor(defaultCtor) {}
		Serializable() = default;
		Serializable(const Serializable&) = default;
		~Serializable() = default;

		std::optional<std::function<RefLib::Variant()>> DefaultConstructor;
	};
}

ARC_REFLECT(Architect::Serializable)