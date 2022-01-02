#pragma once
#include "Rendering-System/Material.h"

namespace Architect
{
	struct SpriteRendererComponent
	{
		Material SpriteMaterial;

		SpriteRendererComponent(Material mat = Material()) : SpriteMaterial(mat) {}
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		~SpriteRendererComponent() = default;
	};
}
