#pragma once
#include "Scene.h"
#include "Entity.h"
#include "Entity-Components/Basic-Components.h"
#include <functional>

namespace Architect
{
	class EntitySystem
	{
	public:
		EntitySystem();
		~EntitySystem();

		void Update(Scene* scene, float timeStep);

		void OnAddedToGameWorld(std::vector<Scene*> currentScenes);
		void OnRemovedFromGameWorld(std::vector<Scene*> currentScenes);
		void OnSceneAdded(Scene* scene);
		void OnSceneRemoved(Scene* scene);

	protected:
		virtual void OnUpdate(float timeStep) = 0;

		virtual void OnStart() {}
		virtual void OnStop() {}
		
		template<typename TComponent>
		void GetEntitiesWithComponent(std::function<void(Entity&, TComponent&)> onEntity)
		{
			auto view = m_CurrentScene->m_EntityRegistry.view<TComponent>();
			for (auto entity : view)
			{
				Entity e = Entity(entity, m_CurrentScene);
				onEntity(e, view.get<TComponent>(entity));
			}
		}

		template<typename TComponent>
		void RunFuncOnEntites(std::function<void(TComponent&)> onEntity)
		{
			auto view = m_CurrentScene->m_EntityRegistry.view<TComponent>();
			for (auto entity : view)
			{
				onEntity(view.get<TComponent>(entity));
			}
		}

		template<typename TComponent1, typename TComponent2>
		void RunFuncOnEntites(std::function<void(TComponent1&, TComponent2&)> onEntity)
		{
			auto group = m_CurrentScene->m_EntityRegistry.group<TComponent1>(entt::get<TComponent2>);
			for (auto entity : group)
			{
				onEntity(group.get<TComponent1>(entity), group.get<TComponent2>(entity));
			}
		}

		template<typename TComponent1, typename TComponent2, typename TComponent3>
		void RunFuncOnEntites(std::function<void(TComponent1&, TComponent2&, TComponent3&)> onEntity)
		{
			auto group = m_CurrentScene->m_EntityRegistry.group<TComponent1>(entt::get<TComponent2, TComponent3>);
			for (auto entity : group)
			{
				onEntity(group.get<TComponent1>(entity), group.get<TComponent2>(entity), group.get<TComponent3>(entity));
			}
		}

		template<typename TComponent1, typename TComponent2, typename TComponent3, typename TComponent4>
		void RunFuncOnEntites(std::function<void(TComponent1&, TComponent2&, TComponent3&, TComponent4&)> onEntity)
		{
			auto group = m_CurrentScene->m_EntityRegistry.group<TComponent1>(entt::get<TComponent2, TComponent3, TComponent4>);
			for (auto entity : group)
			{
				onEntity(group.get<TComponent1>(entity), group.get<TComponent2>(entity), group.get<TComponent3>(entity), group.get<TComponent4>(entity));
			}
		}

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
			OnDestroyComponentEventLisenerData(std::function<void(entt::registry&)> addLisenerFunc, std::function<void(entt::registry&)> removeLisenerFunc, IDestroyComponentEventLisener* lisener)
			{
				AddLisenerFunc = addLisenerFunc;
				RemoveLisenerFunc = removeLisenerFunc;
				Lisener = lisener;
			}

			std::function<void(entt::registry&)> AddLisenerFunc;
			std::function<void(entt::registry&)> RemoveLisenerFunc;
			IDestroyComponentEventLisener* Lisener;

			inline bool operator==(const OnDestroyComponentEventLisenerData& other) { return this->Lisener == other.Lisener; }
		};

		template<typename T>
		OnDestoryComponentLisener<T>* AddLisenerToOnComponentDestroyed(std::function<void(T&)> func)
		{
			OnDestoryComponentLisener<T>* lisener = new OnDestoryComponentLisener<T>(func);

			std::function<void(entt::registry&)> addLisenerFunction = [=](entt::registry& registry)
			{
				registry.on_destroy<T>().connect<&IDestroyComponentEventLisener::Invoke>(lisener);
			};

			std::function<void(entt::registry&)> removeLisenerFunction = [=](entt::registry& registry)
			{
				registry.on_destroy<T>().disconnect<&IDestroyComponentEventLisener::Invoke>(lisener);
			};

			m_DestroyComponentEventLiseners.emplace_back(addLisenerFunction, removeLisenerFunction, lisener);
			return lisener;
		}

		void RemoveLisenerFromOnComponentDestroyed(IDestroyComponentEventLisener* lisener);

	private:
		Scene* m_CurrentScene;
		std::vector<Scene*> m_WorldScenes;
		std::vector<OnDestroyComponentEventLisenerData> m_DestroyComponentEventLiseners;
	};
}

