#include "SceneManager.h"

namespace Architect
{
	Scene* SceneManager::m_ActiveScene;
	EventHandler<void> SceneManager::m_ActiveSceneChangedEventHandler;

	void SceneManager::SetActiveScene(Scene* scene)
	{
		if (m_ActiveScene != nullptr)
			m_ActiveScene->ClearOnComponentDestroyedLiseners();

		m_ActiveScene = scene;

		m_ActiveSceneChangedEventHandler.Invoke();
	}
}
