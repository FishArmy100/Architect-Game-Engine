#pragma once
#include "Entity-Component-System/Scene.h"
#include <functional>
#include <vector>
#include "Core/Events.h"

namespace Architect
{
	class SceneManager
	{
	public:
		static void SetActiveScene(Scene* scene);
		static EventHandler<void>& GetActiveSceneChangedEventHandler() { return m_ActiveSceneChangedEventHandler; }
		static Scene* GetActiveScene() { return m_ActiveScene; }

	private:
		static Scene* m_ActiveScene;
		static EventHandler<void> m_ActiveSceneChangedEventHandler;
	};
}

