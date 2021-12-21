#include "EntitySystem.h"

namespace Architect
{
	EntitySystem::EntitySystem()
	{
		m_CurrentScene = nullptr;
	}

	EntitySystem::~EntitySystem()
	{

	}

	void EntitySystem::Update(Scene* scene, float timeStep)
	{
		m_CurrentScene = scene;
		OnUpdate(timeStep);
	}
}