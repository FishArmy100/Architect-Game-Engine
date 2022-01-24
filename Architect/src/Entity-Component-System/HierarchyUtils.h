#pragma once
#include "Scene.h"

namespace Architect
{
	class HierarchyUtils
	{
	public:
		static void SetParent(Scene* scene, EntityID entity, EntityID parent);
		static void ClearParent(Scene* scene, EntityID entity);
	};
}

