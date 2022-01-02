#pragma once
#include <string>
#include "entt/entt.hpp"
#include <functional>

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

		friend class Entity;

	public:
		Scene(const std::string& name = "Scene");

		unsigned long long int GetID() { return m_SceneID; }

		std::string GetName() { return m_Name; }

		Entity CreateEntity(const std::string& name);
		void DestroyEntity(Entity e);

		template<typename TComponent>
		void GetEntitiesWithComponent(std::function<void(Entity&, TComponent&)> onEntity)
		{
			auto view = m_EntityRegistry.view<TComponent>();
			for (auto entity : view)
			{
				Entity e = Entity(entity, this);
				onEntity(e, view.get<TComponent>(entity));
			}
		}

		template<typename TComponent>
		void RunFuncOnEntites(std::function<void(TComponent&)> onEntity)
		{
			auto view = m_EntityRegistry.view<TComponent>();
			for (auto entity : view)
			{
				onEntity(view.get<TComponent>(entity));
			}
		}

		template<typename TComponent1, typename TComponent2>
		void RunFuncOnEntites(std::function<void(TComponent1&, TComponent2&)> onEntity)
		{
			auto group = m_EntityRegistry.group<TComponent1>(entt::get<TComponent2>);
			for (auto entity : group)
			{
				onEntity(group.get<TComponent1>(entity), group.get<TComponent2>(entity));
			}
		}

		template<typename TComponent1, typename TComponent2, typename TComponent3>
		void RunFuncOnEntites(std::function<void(TComponent1&, TComponent2&, TComponent3&)> onEntity)
		{
			auto group = m_EntityRegistry.group<TComponent1>(entt::get<TComponent2, TComponent3>);
			for (auto entity : group)
			{
				onEntity(group.get<TComponent1>(entity), group.get<TComponent2>(entity), group.get<TComponent3>(entity));
			}
		}

		template<typename TComponent1, typename TComponent2, typename TComponent3, typename TComponent4>
		void RunFuncOnEntites(std::function<void(TComponent1&, TComponent2&, TComponent3&, TComponent4&)> onEntity)
		{
			auto group = m_EntityRegistry.group<TComponent1>(entt::get<TComponent2, TComponent3, TComponent4>);
			for (auto entity : group)
			{
				onEntity(group.get<TComponent1>(entity), group.get<TComponent2>(entity), group.get<TComponent3>(entity), group.get<TComponent4>(entity));
			}
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
