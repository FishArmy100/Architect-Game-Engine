#pragma once
#include <vector>
#include "Entity-Component-System/EntityID.h"

namespace Architect
{
	struct HierarchyComponent
	{
		EntityID Parent;
		std::vector<EntityID> Children;
	};
}