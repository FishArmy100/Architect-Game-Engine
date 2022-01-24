#pragma once
#include "RenderEntitySystem.h"
#include "Rendering-System/Renderer.h"

namespace Architect
{
	class SpriteRendererSystem : public RenderEntitySystem
	{
	public:
		SpriteRendererSystem();
		void OnRender(std::shared_ptr<Scene> scene) override;
	};
}
