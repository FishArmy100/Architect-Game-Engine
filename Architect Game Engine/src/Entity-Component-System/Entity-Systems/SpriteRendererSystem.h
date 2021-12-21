#pragma once
#include "Entity-Component-System/EntitySystem.h"
#include "Entity-Component-System/Entity-Components/Basic-Components.h"
#include "Entity-Component-System/Entity-Components/SpriteRendererComponent.h"
#include "Rendering-System/Renderer.h"

namespace Architect
{
	class SpriteRendererSystem : public EntitySystem
	{
	private:
		Renderer* m_Renderer;

	public:
		SpriteRendererSystem(Renderer* renderer);

	protected:
		void OnUpdate(float timeStep) override;

		void OnEntity(TransformComponent& transform, SpriteRendererComponent& spriteRenderer, unsigned int indicies[6], float positions[16]);
	};
}

