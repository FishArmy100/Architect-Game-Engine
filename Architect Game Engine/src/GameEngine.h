#pragma once
#include "LayerStack.h"

namespace Architect
{
	class GameEngine
	{
	public:
		static GameEngine Create(std::vector<Layer*>& layers);

		void Start();
		static void ShutDown();

		~GameEngine();

	private:
		static GameEngine* m_Instance;

		bool m_IsRunning;

		LayerStack m_LayerStack;
		void UpdateLayers();

		GameEngine(std::vector<Layer*>& layers);
	};
}

