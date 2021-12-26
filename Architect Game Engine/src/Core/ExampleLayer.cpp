#include "ExampleLayer.h"
#include "Logger/Logger.h"

namespace Architect
{
	void ExampleLayer::OnAttach()
	{
		ARC_INFO("Example Layer Attached");
	}

	void ExampleLayer::OnDetach()
	{
		ARC_INFO("Example Layer Detached");
	}

	void ExampleLayer::OnUpdate(float timestep)
	{
		ARC_INFO("Example Layer Update");
	}
}