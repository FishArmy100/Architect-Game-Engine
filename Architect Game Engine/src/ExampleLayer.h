#pragma once
#include "Layer.h"

namespace Architect
{
	class ExampleLayer : public Layer
	{
	public:
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
	};
}

