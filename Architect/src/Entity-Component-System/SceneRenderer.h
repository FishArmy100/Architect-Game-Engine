#pragma once
#include "Scene.h"
#include "Rendering-System/Rendering.h"
#include "Entity-Component-System/Entity-Components/Basic-Components.h"

namespace Architect
{
	class SceneRenderer
	{
	public:
		static void RenderScene(std::shared_ptr<Scene> scene);

	private:
		static void OnSpriteEntity(TransformComponent& transform, SpriteRendererComponent& spriteRenderer, unsigned int indicies[6], float positions[16]);
	};
}

