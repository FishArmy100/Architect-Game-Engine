#pragma once
#include <vector>
#include "Entity-Component-System/EntityID.h"
#include "Reflection/RegistrationMacros.h"

namespace Architect
{
	struct HierarchyComponent
	{
		EntityID Parent = NullEntity;
		std::vector<EntityID> Children{};
	};
}

ARC_REFLECT_AUTO(Architect::HierarchyComponent)