#pragma once
#include "Core/Layer.h"

namespace Architect
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		bool OnEvent(IApplicationEvent* appEvent) override;

		void Begin();
		void End();

	};
}

