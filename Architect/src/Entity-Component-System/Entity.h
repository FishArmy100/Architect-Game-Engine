#pragma once
#include "entt/entt.hpp"
#include "Scene.h"
#include "Entity-Components/Basic-Components.h"
#include "EntityID.h"

namespace Architect
{
	class Entity
	{
	public:
		Entity(EntityID handle, Scene* scene);
		Entity(const Entity& other) = default;

		Entity() = default;

		void SetName(const std::string& name);
		std::string& GetName() { return GetComponent<EntityDataComponent>().Name; }

		TransformComponent& GetTransform() { return GetComponent<TransformComponent>(); }

		void SetActive(bool isActive);
		bool IsActive() { return GetComponent<EntityDataComponent>().IsActive; }

		uint64_t GetUUID() { return GetComponent<EntityDataComponent>().GetUUID(); }

		void SetParent(EntityID e);
		EntityID GetParentID() { return GetComponent<HierarchyComponent>().Parent; }
		bool GetHasParent() { return GetParentID() != NullEntity; }
		std::vector<Entity> GetChildren();
		std::vector<EntityID> GetChildrenIDs() { return GetComponent<HierarchyComponent>().Children; }

		Scene* GetScene() { return m_Scene; }

		template<typename T>
		bool ContainsComponent()
		{
			return m_Scene->EntityContainsComponent<T>(m_EntityHandle);
		}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return m_Scene->AddComponentToEntity<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			return m_Scene->GetComponentFromEntity<T>(m_EntityHandle);
		}

		template<typename T>
		bool RemoveComponent()
		{
			return m_Scene->RemoveComponentFromEntity<T>(m_EntityHandle);
		}

		template<typename T>
		bool TryGetComponent(T*& outComponent)
		{
			return m_Scene->TryGetComponent<T>(m_EntityHandle, outComponent);
		}

		bool operator==(const Entity& lhs) const
		{
			return this->m_EntityHandle == lhs.m_EntityHandle && this->m_Scene == lhs.m_Scene;
		}

		bool operator!=(const Entity& lhs) const { return !(*this == lhs); }

		operator bool() const { return m_EntityHandle != entt::null; }
		operator EntityID() const{ return m_EntityHandle; }

	private:
		EntityID m_EntityHandle = entt::null;
		Scene* m_Scene = nullptr;
	};
}

