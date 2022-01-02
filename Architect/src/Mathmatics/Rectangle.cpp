#include "Rectangle.h"
#include <sstream>

namespace Architect
{
	Rectangle::Rectangle(Vector2 position, Vector2 dimentions)
	{
		Position = position;
		Width = dimentions.X;
		Height = dimentions.Y;
	}

	Rectangle::Rectangle(Vector2 position, float width, float height)
	{
		Position = position;
		Width = width;
		Height = height; 
	}

	Rectangle::Rectangle(float x, float y, float width, float height)
	{
		Position = Vector2(x, y);
		Width = width;
		Height = height;
	}

	bool Rectangle::ContainsPoint(const Vector2& point) const 
	{
		bool isInWidth = point.X >= Position.X && point.X <= Position.X + Width;
		bool isInHeight = point.Y >= Position.Y && point.Y <= Position.Y + Height;
		return isInHeight && isInWidth;
	}

	Vector2 Rectangle::GetDimentions() const
	{
		return Vector2(Width, Height);
	}

	std::string Rectangle::ToString() const
	{
		std::stringstream ss;
		ss << "Position: " << Position.ToString() << ", Width: " << Width << ", Height: " << Height;
		return ss.str();
	}
}