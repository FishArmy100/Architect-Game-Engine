#pragma once
#include "entt/entt.hpp"
#include <memory>
#include <vector>
#include "Scene.h"
#include "Entity.h"
#include "EntitySystem.h"

namespace Architect
{
	class Entity;

	class GameWorld
	{
	private:
		std::vector<Scene*> m_Scenes;
		std::vector<EntitySystem*> m_EntitySystems;

	public:
		GameWorld();
		~GameWorld();

		void AddScene(Scene* scene);
		void RemoveScene(Scene* scene);
		bool ContainsScene(Scene* scene);

		std::vector<Scene*> GetScenes() { return m_Scenes; }

		void AddEntitySystem(EntitySystem* system);
		void RemoveEntitySystem(EntitySystem* system);
		bool ContainsEntitySystem(EntitySystem* system);

		void UpdateSystems();
		
		std::vector<EntitySystem*> GetSystems() { return m_EntitySystems; }
	};
}

