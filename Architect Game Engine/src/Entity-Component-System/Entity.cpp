#include "Entity.h"
#include "Entity-Components/Basic-Components.h"

namespace Architect
{
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

	void Entity::SetActive(bool isActive)
	{
		GetComponent<IsActiveComponent>().IsActive = isActive;
	}
}
