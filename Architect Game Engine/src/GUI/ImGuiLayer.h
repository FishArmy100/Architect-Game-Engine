#pragma once
#include "Core/Layer.h"

namespace Architect
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void Begin();
		void End();

	};
}

