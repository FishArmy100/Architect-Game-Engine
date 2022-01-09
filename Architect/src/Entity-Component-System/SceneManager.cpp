#include "SceneManager.h"

namespace Architect
{
	std::shared_ptr<Scene> SceneManager::m_ActiveScene;
	EventHandler<void> SceneManager::m_ActiveSceneChangedEventHandler;

	void SceneManager::SetActiveScene(std::shared_ptr<Scene> scene)
	{
		if (m_ActiveScene != nullptr)
			m_ActiveScene->ClearOnComponentDestroyedLiseners();

		m_ActiveScene = scene;

		m_ActiveSceneChangedEventHandler.Invoke();
	}
}
