#pragma once
#include "Vectors/Vector2.h"
#include <string>

namespace Architect
{
	class Ray2D
	{
	public:
		Vector2 Origen;
		Vector2 Direction;

		Ray2D(Vector2 origen, Vector2 direction);
		Ray2D(float origenX, float origenY, float directionX, float directionY);

		Vector2 GetDiretionNormalized() const;

		std::string ToString() const;
	};
}

