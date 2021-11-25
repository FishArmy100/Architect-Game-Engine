#pragma once
#include <string>

namespace Architect
{
	class Vector2
	{
	public:
		float X;
		float Y;

		Vector2(float x = 0.0f, float y = 0.0f);
		float Length() const;
		Vector2 Normalize() const;

		static float Distance(const Vector2& a, const Vector2& b);

		std::string ToString() const;

		Vector2 operator+ (const Vector2& v) const
		{
			float x = this->X + v.X;
			float y = this->Y + v.Y;
			return Vector2(x, y);
		}

		Vector2 operator- (const Vector2& v) const
		{
			float x = this->X - v.X;
			float y = this->Y - v.Y;
			return Vector2(x, y);
		}

		Vector2 operator* (const float& value) const
		{
			float x = this->X * value;
			float y = this->Y * value;
			return Vector2(x, y);
		}

		Vector2 operator/ (const float& value) const
		{
			float x = this->X / value;
			float y = this->Y / value;
			return Vector2(x, y);
		}

		Vector2 operator* (const int& value) const
		{
			float x = this->X * (float)value;
			float y = this->Y * (float)value;
			return Vector2(x, y);
		}

		Vector2 operator/ (const int& value) const
		{
			float x = this->X / (float)value;
			float y = this->Y / (float)value;
			return Vector2(x, y);
		}
	};
}

