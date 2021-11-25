#pragma once
#include "Vectors/Vector2.h"
#include <string>

namespace Architect
{
	class Rectangle
	{
	public:
		Vector2 Position;
		float Width;
		float Height;

		Rectangle(Vector2 position, Vector2 dimentions);
		Rectangle(Vector2 position, float width, float height);
		Rectangle(float x, float y, float width, float height);

		bool ContainsPoint(const Vector2& point) const;
		Vector2 GetDimentions() const;

		std::string ToString() const;
	};
}

