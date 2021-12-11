#pragma once
#include "Layer.h"
#include <vector>
#include <functional>

namespace Architect
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		
		int GetLength() { return m_Layers.size(); }
		Layer* GetLayer(int index) { return m_Layers[index]; }

	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerInsert;
	};
}

