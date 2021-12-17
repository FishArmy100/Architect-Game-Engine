#pragma once

#include "entt/entt.hpp"
#include "Scene.h"

namespace Architect
{
	class Entity
	{
	private:
		entt::entity m_EntityHandle = entt::null;
		Scene* m_Scene = nullptr;

	public:
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		Entity() = default;

		template<typename T>
		bool ContainsComponent()
		{
			return m_Scene->m_EntityRegistry.any_of<T>(m_EntityHandle);
		}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return m_Scene->m_EntityRegistry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			return m_Scene->m_EntityRegistry.get<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
	};
}

