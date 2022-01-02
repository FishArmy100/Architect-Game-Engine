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
	};
}

