#include "Entity.h"
#include "Basic-Components/Basic-Components.h"

namespace Architect
{
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}
}
