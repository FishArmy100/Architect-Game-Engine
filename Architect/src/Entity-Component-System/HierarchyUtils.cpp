#include "HierarchyUtils.h"
#include "Entity-Components/HierarchyComponent.h"

namespace Architect
{
	void HierarchyUtils::SetParent(Scene* scene, EntityID entity, EntityID parent)
	{
		if (parent == NullEntity)
		{
			ClearParent(scene, entity);
		}
		else
		{
			scene->GetComponentFromEntity<HierarchyComponent>(entity).Parent = parent;
			scene->GetComponentFromEntity<HierarchyComponent>(parent).Children.push_back(entity);
		}
	}

	void HierarchyUtils::ClearParent(Scene* scene, EntityID entity)
	{
		HierarchyComponent& hierarchy = scene->GetComponentFromEntity<HierarchyComponent>(entity);
		EntityID parent = hierarchy.Parent;

		std::vector<EntityID>& parentChildren = scene->GetComponentFromEntity<HierarchyComponent>(parent).Children;

		auto it = std::find(parentChildren.begin(), parentChildren.end(), entity);
		if (it != parentChildren.end())
			parentChildren.erase(it);

		hierarchy.Parent = NullEntity;
	}
}
