#include "Scene.h"
#include "Mathmatics/UUID.h"
#include "Entity.h"
#include "Entity-Components/Basic-Components.h"

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

	void Scene::DestroyEntity(Entity e)
	{
		m_EntityRegistry.destroy(e);
	}

	void Scene::RemoveLisenerFromOnComponentDestroyed(IDestroyComponentEventLisener* lisener)
	{
		for (auto& activeLisener : m_DestroyComponentEventLiseners)
		{
			if (activeLisener.Lisener == lisener)
			{
				activeLisener.RemoveLisenerFunc(m_EntityRegistry);

				auto index = std::find(m_DestroyComponentEventLiseners.begin(), m_DestroyComponentEventLiseners.end(), activeLisener);
				if (index != m_DestroyComponentEventLiseners.end())
					m_DestroyComponentEventLiseners.erase(index);
			}
		}

		delete lisener;
	}

	void Scene::ClearOnComponentDestroyedLiseners()
	{
		for (auto& lisener : m_DestroyComponentEventLiseners)
		{
			lisener.RemoveLisenerFunc(m_EntityRegistry);
		}
	}
}
