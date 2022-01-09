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
		static void SetActiveScene(std::shared_ptr<Scene> scene);
		static EventHandler<void>& GetActiveSceneChangedEventHandler() { return m_ActiveSceneChangedEventHandler; }
		static std::shared_ptr<Scene> GetActiveScene() { return m_ActiveScene; }

	private:
		static std::shared_ptr<Scene> m_ActiveScene;
		static EventHandler<void> m_ActiveSceneChangedEventHandler;
	};
}

