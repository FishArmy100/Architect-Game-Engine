#include "Scene.h"
#include "Mathmatics/UUID.h"
#include "Entity.h"
#include "Entity-Components/Basic-Components.h"
#include "HierarchyUtils.h"

namespace Architect
{
	Scene::Scene(const std::string& name) : m_Name(name), m_SceneID(UUID::NewUUID())
	{

	}

	EntityID Scene::CreateRawEntity(const std::string& name)
	{
		entt::entity e = m_EntityRegistry.create();
		m_EntityRegistry.emplace<EntityDataComponent>(e, name);
		m_EntityRegistry.emplace<TransformComponent>(e);
		m_EntityRegistry.emplace<HierarchyComponent>(e);
		m_CurrentEntites.push_back(e);
		return e;
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		EntityID id = CreateRawEntity(name);
		return Entity(id, this);
	}

	void Scene::DestoryEntity(EntityID e)
	{
		for (EntityID decendent : HierarchyUtils::GetDecendents(this, e))
		{
			auto it = std::find(m_CurrentEntites.begin(), m_CurrentEntites.end(), decendent);
			m_CurrentEntites.erase(it);
			m_EntityRegistry.destroy(decendent);
		}

		auto it = std::find(m_CurrentEntites.begin(), m_CurrentEntites.end(), e);
		m_CurrentEntites.erase(it);

		m_EntityRegistry.destroy(e);
	}

	void Scene::DestroyEntity(Entity e)
	{
		DestoryEntity((EntityID)e);
	}

	void Scene::MoveEntity(size_t oldIndex, size_t newIndex)
	{
		if (oldIndex > newIndex)
			std::rotate(m_CurrentEntites.rend() - oldIndex - 1, m_CurrentEntites.rend() - oldIndex, m_CurrentEntites.rend() - newIndex);
		else
			std::rotate(m_CurrentEntites.begin() + oldIndex, m_CurrentEntites.begin() + oldIndex + 1, m_CurrentEntites.begin() + newIndex + 1);
	}

	std::optional<size_t> Scene::IndexOf(EntityID entity)
	{
		auto it = std::find(m_CurrentEntites.begin(), m_CurrentEntites.end(), entity);

		if (it == m_CurrentEntites.end())
			return {};

		return it - m_CurrentEntites.begin();
	}

	std::optional<Entity> Scene::operator[](size_t index)
	{
		if (index >= m_CurrentEntites.size())
			return {};

		return Entity(m_CurrentEntites[index], this);
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
