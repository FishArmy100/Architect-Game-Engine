#include "GameWorld.h"
#include "Entity.h"
#include "GL/glew.h"

namespace Architect
{
	GameWorld::GameWorld()
	{

	}

	GameWorld::~GameWorld()
	{
		for (Scene* scene : m_Scenes)
			delete scene;

		for (EntitySystem* system : m_EntitySystems)
			delete system;
	}

	void GameWorld::AddScene(Scene* scene)
	{
		if(!ContainsScene(scene))
			m_Scenes.push_back(scene);
	}

	void GameWorld::RemoveScene(Scene* scene)
	{
		if (ContainsScene(scene))
		{
			std::vector<Scene*>::iterator index = std::find(m_Scenes.begin(), m_Scenes.end(), scene);
			m_Scenes.erase(index);
		}
	}

	bool GameWorld::ContainsScene(Scene* scene)
	{
		return std::find(m_Scenes.begin(), m_Scenes.end(), scene) != m_Scenes.end();
	}

	void GameWorld::AddEntitySystem(EntitySystem* system)
	{
		if (!ContainsEntitySystem(system))
			m_EntitySystems.push_back(system);
	}

	void GameWorld::RemoveEntitySystem(EntitySystem* system)
	{
		if (ContainsEntitySystem(system))
		{
			std::vector<EntitySystem*>::iterator index = std::find(m_EntitySystems.begin(), m_EntitySystems.end(), system);
			m_EntitySystems.erase(index);
		}
	}

	bool GameWorld::ContainsEntitySystem(EntitySystem* system)
	{
		return std::find(m_EntitySystems.begin(), m_EntitySystems.end(), system) != m_EntitySystems.end(); 
	}

	void GameWorld::UpdateSystems(float timeStep)
	{
		

		for (EntitySystem* system : m_EntitySystems)
		{
			for (Scene* scene : m_Scenes)
			{
				system->Update(scene, timeStep);
			}
		}
	}
}