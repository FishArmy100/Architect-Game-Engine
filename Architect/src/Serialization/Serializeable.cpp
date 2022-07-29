#include "Serializeable.h"
#include "RefLib/Registration/HelperRegistrationMacros.h"
#include "Reflection/RegistrationMacros.h"

ARC_BEGIN_CLASS(Architect::Serializable)
	REFLIB_CTOR()
	REFLIB_CTOR(const Architect::Serializable&)
	REFLIB_CTOR(std::optional<std::function<RefLib::Variant()>>)
	REFLIB_PROP_BASIC(DefaultConstructor)
ARC_END_CLASS()