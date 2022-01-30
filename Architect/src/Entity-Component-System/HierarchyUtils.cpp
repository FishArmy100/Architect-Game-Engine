#include "HierarchyUtils.h"
#include "Entity-Components/HierarchyComponent.h"
#include "Entity-Components/TransformComponent.h"

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

	bool HierarchyUtils::ContainsDecedent(Scene* scene, EntityID entity, EntityID decendent)
	{
		std::vector<EntityID> entityChildren = scene->GetComponentFromEntity<HierarchyComponent>(entity).Children;

		if (entityChildren.size() < 1)
			return false;

		for (EntityID child : entityChildren)
		{
			if (child == decendent)
				return true;

			if (ContainsDecedent(scene, child, decendent))
				return true;
		}

		return false;
	}

	static glm::mat4 GetWorldPositionFromLocalPosition(Scene* scene, EntityID entity)
	{
		HierarchyComponent& hierarchy = scene->GetComponentFromEntity<HierarchyComponent>(entity);
		TransformComponent& transform = scene->GetComponentFromEntity<TransformComponent>(entity);

		if (hierarchy.Parent == NullEntity)
			return transform.LocalToParent;
		else
			return GetWorldPositionFromLocalPosition(scene, hierarchy.Parent) * transform.LocalToParent;
	}

	glm::mat4 HierarchyUtils::LocalToWorld(Scene* scene, EntityID parent, glm::mat4 localTransform)
	{
		return GetWorldPositionFromLocalPosition(scene, parent) * localTransform;
	}

	glm::mat4 HierarchyUtils::WorldToLocal(Scene* scene, EntityID parent, glm::mat4 worldTransform)
	{
		return glm::inverse(LocalToWorld(scene, parent, glm::identity<glm::mat4>())) * worldTransform;
	}

	static void GetDecendentsInternal(Scene* scene, EntityID entity, std::vector<EntityID>& decendents)
	{
		HierarchyComponent& h = scene->GetComponentFromEntity<HierarchyComponent>(entity);

		if (h.Children.size() == 0)
			return;
		
		for (EntityID child : h.Children)
		{
			decendents.emplace_back(child);
			GetDecendentsInternal(scene, child, decendents);
		}
	}

	std::vector<EntityID> HierarchyUtils::GetDecendents(Scene* scene, EntityID entity)
	{
		std::vector<EntityID> decendents;
		GetDecendentsInternal(scene, entity, decendents);
		return decendents;
	}
}
