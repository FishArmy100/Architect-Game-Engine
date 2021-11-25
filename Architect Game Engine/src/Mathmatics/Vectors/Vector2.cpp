#include "Vector2.h"
#include "Vector2Internal.h"
#include <cmath>
#include <sstream>

namespace Architect
{
	Vector2::Vector2(float x, float y)
	{
		X = x;
		Y = y;
	}

	float Vector2::Length() const
	{
		return sqrt(pow(this->X, 2) + pow(this->Y, 2));
	}

	Vector2 Vector2::Normalize() const
	{
		return *this / this->Length();
	}

	float Vector2::Distance(const Vector2& a, const Vector2& b)
	{
		float xDifference = a.X - b.X;
		float yDifference = a.Y - b.Y;
		return sqrt(pow(xDifference, 2) + pow(yDifference, 2));
	}

	std::string Vector2::ToString() const
	{
		std::stringstream ss;
		ss << "(" << X << ", " << Y << ")";
		return ss.str();
	}
}