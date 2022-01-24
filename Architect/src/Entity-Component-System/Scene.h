#pragma once
#include <string>
#include "entt/entt.hpp"
#include <functional>
#include "EntityID.h"

namespace Architect
{
	class Entity;

	class IDestroyComponentEventLisener
	{
	public:
		virtual void Invoke(entt::registry& registry, entt::entity entity) = 0;
	};

	template<typename T>
	class OnDestoryComponentLisener : public IDestroyComponentEventLisener
	{
	public:
		OnDestoryComponentLisener(std::function<void(T&)> func)
		{
			m_Func = func;
		}

		void Invoke(entt::registry& registry, entt::entity entity) override
		{
			m_Func(registry.get<T>(entity));
		}

	private:
		std::function<void(T&)> m_Func;
	};

	struct OnDestroyComponentEventLisenerData
	{
		OnDestroyComponentEventLisenerData(std::function<void(entt::registry&)> removeLisenerFunc, IDestroyComponentEventLisener* lisener)
		{
			RemoveLisenerFunc = removeLisenerFunc;
			Lisener = lisener;
		}

		std::function<void(entt::registry&)> RemoveLisenerFunc;
		IDestroyComponentEventLisener* Lisener;

		inline bool operator==(const OnDestroyComponentEventLisenerData& other) { return this->Lisener == other.Lisener; }
	};

	class Scene
	{
	private:
		unsigned long long int m_SceneID;
		std::string m_Name;
		entt::registry m_EntityRegistry;
		std::vector<OnDestroyComponentEventLisenerData> m_DestroyComponentEventLiseners;

	public:
		Scene(const std::string& name = "Scene");

		unsigned long long int GetID() { return m_SceneID; }

		std::string GetName() { return m_Name; }

		EntityID CreateRawEntity(const std::string& name);
		Entity CreateEntity(const std::string& name);
		void DestoryEntity(EntityID e);
		void DestroyEntity(Entity e);

		template<typename ...TComponent>
		void GetEntitiesWithComponent(std::function<void(TComponent&...)> onEntity)
		{
			auto view = m_EntityRegistry.view<TComponent...>();
			for (auto entity : view)
			{
				onEntity(view.get<TComponent>(entity)...);
			}
		}

		template<typename ...TComponents>
		void GetEntitiesWithComponent(std::function<void(Entity&, TComponents&...)> onEntity)
		{
			auto view = m_EntityRegistry.view<TComponents...>();
			for (auto entity : view) 
			{
				Entity e = Entity(entity, this);
				onEntity(e, view.get<TComponents>(entity)...);
			}
		}

		template<typename ...TComponents>
		entt::view<TComponents...> GetRawView()
		{
			return m_EntityRegistry.view<TComponents...>();
		}

		template<typename T>
		bool EntityContainsComponent(EntityID entity)
		{
			return m_EntityRegistry.any_of<T>(entity);
		}

		template<typename T, typename... Args>
		T& AddComponentToEntity(EntityID entity, Args&&... args) 
		{
			return m_EntityRegistry.emplace<T>(entity, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponentFromEntity(EntityID entity)
		{
			return m_EntityRegistry.get<T>(entity);
		}

		template<typename T>
		bool RemoveComponentFromEntity(EntityID entity)
		{
			if (EntityContainsComponent<T>(entity))
			{
				m_EntityRegistry.remove<T>(entity);
				return true;
			}

			return false;
		}

		template<typename T>
		bool TryGetComponent(EntityID entity, T*& outComponent)
		{
			if (EntityContainsComponent<T>(entity))
			{
				outComponent = &GetComponentFromEntity<T>(entity);
				return true;
			}

			outComponent = nullptr;
			return false;
		}

		template<typename T>
		OnDestoryComponentLisener<T>* AddLisenerToOnComponentDestroyed(std::function<void(T&)> func)
		{
			OnDestoryComponentLisener<T>* lisener = new OnDestoryComponentLisener<T>(func);

			m_EntityRegistry.on_destroy<T>().connect<&IDestroyComponentEventLisener::Invoke>(lisener);

			std::function<void(entt::registry&)> removeLisenerFunction = [=](entt::registry& registry)
			{
				registry.on_destroy<T>().disconnect<&IDestroyComponentEventLisener::Invoke>(lisener);
			};

			m_DestroyComponentEventLiseners.emplace_back(removeLisenerFunction, lisener);
			return lisener;
		}

		void RemoveLisenerFromOnComponentDestroyed(IDestroyComponentEventLisener* lisener);
		void ClearOnComponentDestroyedLiseners();
	};
}

