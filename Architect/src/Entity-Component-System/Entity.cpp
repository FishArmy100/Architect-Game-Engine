#include "Entity.h"
#include "Entity-Components/Basic-Components.h"
#include "HierarchyUtils.h"

namespace Architect
{
	Entity::Entity(EntityID handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

	void Entity::SetName(const std::string& name)
	{
		GetComponent<EntityDataComponent>().Name = name;
	}

	void Entity::SetActive(bool isActive)
	{
		GetComponent<EntityDataComponent>().IsActive = isActive;
	}

	void Entity::SetParent(EntityID e)
	{
		HierarchyUtils::SetParent(m_Scene, m_EntityHandle, e);
	}

	std::vector<Entity> Entity::GetChildren()
	{
		std::vector<Entity> children{};
		for (auto childID : GetChildrenIDs())
		{
			children.emplace_back(childID, m_Scene);
		}

		return children;
	}
}
