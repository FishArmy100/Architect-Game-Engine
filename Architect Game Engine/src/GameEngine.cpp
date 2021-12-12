#include "GameEngine.h"
#include <GL/glew.h>
#include "Logger/Logger.h"
#include <memory>

namespace Architect
{
	GameEngine* GameEngine::m_Instance;

	GameEngine GameEngine::Create(std::vector<Layer*>& layers)
	{
		if (m_Instance != nullptr)
		{
			ARC_ENGINE_ERROR("Tried to create a second instance of a Game Engine");
			return GameEngine(layers);
		}
		else
		{
			m_Instance = new GameEngine(layers);
			return *m_Instance;
		}
	}

	void GameEngine::Start()
	{
		while (m_IsRunning)
		{
			UpdateLayers();
		}
	}

	void GameEngine::ShutDown()
	{
		m_Instance->m_IsRunning = false;
	}

	void GameEngine::UpdateLayers()
	{
		for (int i = 0; i < m_LayerStack.GetLength(); i++)
			m_LayerStack.GetLayer(i)->OnUpdate();
	}

	GameEngine::GameEngine(std::vector<Layer*>& layers) : m_IsRunning(true)
	{
		for (Layer* layer : layers)
			m_LayerStack.PushLayer(layer);
	}

	GameEngine::~GameEngine()
	{

	}
}
