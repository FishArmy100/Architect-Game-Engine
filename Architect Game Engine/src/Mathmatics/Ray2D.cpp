#include "Ray2D.h"
#include <sstream>

namespace Architect
{
	Ray2D::Ray2D(Vector2 origen, Vector2 direction)
	{
		Origen = origen;
		Direction = direction;
	}

	Ray2D::Ray2D(float origenX, float origenY, float directionX, float directionY)
	{
		Origen = Vector2(origenX, origenY);
		Direction = Vector2(directionX, directionY);
	}

	Vector2 Ray2D::GetDiretionNormalized() const
	{
		return Direction.Normalize();
	}

	std::string Ray2D::ToString() const
	{
		std::stringstream ss;
		ss << "Position: " << Origen.ToString() << ", Direction: " << Direction.ToString();
		return ss.str();
	}
}