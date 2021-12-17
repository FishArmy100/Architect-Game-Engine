#include "Scene.h"
#include "Mathmatics/UUID.h"
#include "Entity.h"
#include "Basic-Components/Basic-Components.h"

namespace Architect
{
	Scene::Scene(const std::string& name) : m_Name(name), m_SceneID(UUID::NewUUID())
	{

	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		entt::entity e = m_EntityRegistry.create();
		Entity entity = Entity(e, this);
		entity.AddComponent<TagComponent>(name);
		entity.AddComponent<IsActiveComponent>(true);
		entity.AddComponent<TransformComponent>();
		return entity;
	}
}
