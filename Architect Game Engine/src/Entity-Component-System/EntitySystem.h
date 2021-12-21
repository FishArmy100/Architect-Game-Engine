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

	protected:
		virtual void OnUpdate(float timeStep) = 0;
		
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

	private:
		Scene* m_CurrentScene;
	};
}

