#pragma once

#include "entt/entt.hpp"
#include "Scene.h"
#include "Entity-Components/Basic-Components.h"

namespace Architect
{
	struct Test
	{
		void OnDestroy()
		{

		}
	};

	class Entity
	{
	private:
		entt::entity m_EntityHandle = entt::null;
		Scene* m_Scene = nullptr;

	public:
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		Entity() = default;

		std::string& GetTag() { return (std::string&)GetComponent<TagComponent>(); }

		TransformComponent& GetTransform() { return GetComponent<TransformComponent>(); }

		void SetActive(bool isActive);
		bool IsActive() { return (bool)GetComponent<IsActiveComponent>(); }

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

		template<typename T>
		bool RemoveComponent()
		{
			if (ContainsComponent<T>())
			{
				m_Scene->m_EntityRegistry.remove<T>(m_EntityHandle);
			}

			return false;
		}

		template<typename T>
		bool TryGetComponent(T*& outComponent)
		{
			if (ContainsComponent<T>())
			{
				outComponent = &GetComponent<T>();
				
			}

			outComponent = nullptr;
			return false;
		}

		bool operator==(const Entity& lhs) const
		{
			return this->m_EntityHandle == lhs.m_EntityHandle && this->m_Scene == lhs.m_Scene;
		}

		bool operator!=(const Entity lhs) const { return !(*this == lhs); }

		operator bool() const { return m_EntityHandle != entt::null; }
		operator entt::entity() const{ return m_EntityHandle; }
	};
}

