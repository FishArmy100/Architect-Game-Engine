#include "Color.h"
#include <algorithm>
#include <sstream>

namespace Architect
{
	Color::Color(float r, float g, float b, float a)
	{
		SetRed(r);
		SetGreen(g);
		SetBlue(b);
		SetAlpha(a);
	}

	Color::Color()
		: m_Red(0), m_Green(0), m_Blue(0), m_Alpha(0)
	{

	}

	std::array<float, 4> Color::GetFloatArray() const
	{
		return std::array<float, 4> { m_Red, m_Green, m_Blue, m_Alpha };
	}

	void Color::SetRed(float value)
	{
		m_Red = std::clamp(value, 0.0f, 1.0f);
	}

	void Color::SetGreen(float value)
	{
		m_Green = std::clamp(value, 0.0f, 1.0f);
	}

	void Color::SetBlue(float value)
	{
		m_Blue = std::clamp(value, 0.0f, 1.0f);
	}

	void Color::SetAlpha(float value)
	{
		m_Alpha = std::clamp(value, 0.0f, 1.0f);
	}

	void Color::SetValues(float r, float g, float b, float a)
	{
		SetRed(r);
		SetGreen(g);
		SetBlue(b);
		SetAlpha(a);
	}

	Color Color::White()
	{
		return Color(1, 1, 1, 1);
	}

	Color Color::Black()
	{
		return Color(0, 0, 0, 1);
	}

	Color Color::Clear()
	{
		return Color(0, 0, 0, 0);
	}

	Color Color::Red()
	{
		return Color(1, 0, 0, 1);
	}

	Color Color::Green()
	{
		return Color(0, 1, 0, 1);
	}

	Color Color::Blue()
	{
		return Color(0, 0, 1, 1);
	}

	std::string Color::ToString()
	{
		std::stringstream ss;
		ss << "Red: " << m_Red << ", Green: " << m_Green << ", Blue: " << m_Blue << ", Alpha: " << m_Alpha;
		return ss.str();
	}
}
