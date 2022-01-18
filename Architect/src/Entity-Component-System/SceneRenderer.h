#pragma once
#include "Scene.h"
#include "Rendering-System/Rendering.h"
#include "Entity-Component-System/Entity-Components/Basic-Components.h"
#include "Entity.h"

namespace Architect
{
	class SceneRenderer
	{
	public:
		static void RenderScene(std::shared_ptr<Scene> scene);

	private:
		static void OnSpriteEntity(Entity e, SpriteRendererComponent& spriteRenderer, unsigned int indicies[6], float positions[16]);
	};
}

