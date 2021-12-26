#include "SceneManager.h"

namespace Architect
{
	Scene* SceneManager::m_ActiveScene;
	std::vector<std::function<void()>> SceneManager::m_ActiveSceneChangedLiseners;

	void SceneManager::SetActiveScene(Scene* scene)
	{
		if (m_ActiveScene != nullptr)
			m_ActiveScene->ClearOnComponentDestroyedLiseners();

		m_ActiveScene = scene;

		for (auto onSceneChanged : m_ActiveSceneChangedLiseners)
			onSceneChanged();
	}

	void SceneManager::AddOnActiveSceneChangedLisener(std::function<void()> onSceneChanged)
	{
		m_ActiveSceneChangedLiseners.push_back(onSceneChanged);
	}
}
