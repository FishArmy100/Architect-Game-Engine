#pragma once
#include "Entity-Component-System/Scene.h"
#include <functional>
#include <vector>

namespace Architect
{
	class SceneManager
	{
	public:
		static void SetActiveScene(Scene* scene);
		static void AddOnActiveSceneChangedLisener(std::function<void()> onSceneChanged);
		static Scene* GetActiveScene() { return m_ActiveScene; }

	private:
		static Scene* m_ActiveScene;
		static std::vector<std::function<void()>> m_ActiveSceneChangedLiseners;
	};
}

