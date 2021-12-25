#include "EntitySystem.h"

namespace Architect
{
	EntitySystem::EntitySystem()
	{
		m_CurrentScene = nullptr;
	}

	EntitySystem::~EntitySystem()
	{

	}

	void EntitySystem::Update(Scene* scene, float timeStep)
	{
		m_CurrentScene = scene;
		OnUpdate(timeStep);
	}

	void EntitySystem::OnAddedToGameWorld(std::vector<Scene*> currentScenes)
	{
		m_WorldScenes = currentScenes;
		OnStart();

		for (auto& lisener : m_DestroyComponentEventLiseners)
		{
			for (Scene* scene : currentScenes)
			{
				lisener.AddLisenerFunc(scene->m_EntityRegistry);
			}
		}
	}

	void EntitySystem::OnRemovedFromGameWorld(std::vector<Scene*> currentScenes)
	{
		OnStop();

		for (auto& lisener : m_DestroyComponentEventLiseners)
		{
			for (Scene* scene : currentScenes)
			{
				lisener.RemoveLisenerFunc(scene->m_EntityRegistry);
			}
		}

		m_WorldScenes = std::vector<Scene*>();
	}

	void EntitySystem::OnSceneAdded(Scene* scene)
	{
		for (auto& lisener : m_DestroyComponentEventLiseners)
		{
			lisener.AddLisenerFunc(scene->m_EntityRegistry);
		}

		m_WorldScenes.push_back(scene);
	}

	void EntitySystem::OnSceneRemoved(Scene* scene)
	{
		for (auto& lisener : m_DestroyComponentEventLiseners)
		{
			lisener.RemoveLisenerFunc(scene->m_EntityRegistry);
		}

		auto index = std::find(m_WorldScenes.begin(), m_WorldScenes.end(), scene);
		if (index != m_WorldScenes.end())
			m_WorldScenes.erase(index);
	}

	void EntitySystem::RemoveLisenerFromOnComponentDestroyed(IDestroyComponentEventLisener* lisener)
	{
		for (auto& activeLisener : m_DestroyComponentEventLiseners)
		{
			if (activeLisener.Lisener == lisener)
			{
				for (Scene* scene : m_WorldScenes)
				{
					activeLisener.RemoveLisenerFunc(scene->m_EntityRegistry);
				}

				auto index = std::find(m_DestroyComponentEventLiseners.begin(), m_DestroyComponentEventLiseners.end(), activeLisener);
				if (index != m_DestroyComponentEventLiseners.end())
					m_DestroyComponentEventLiseners.erase(index);
			}
		}

		delete lisener;
	}
}