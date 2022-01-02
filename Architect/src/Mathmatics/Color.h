#pragma once
#include <array>
#include <string>

namespace Architect
{
	class Color
	{
	private:
		float m_Red;
		float m_Green;
		float m_Blue;
		float m_Alpha;

	public:
		Color(float r, float g, float b, float a);
		Color();

		std::array<float, 4> GetFloatArray() const;

		const float GetRed() const { return m_Red; }
		void SetRed(float value);

		const float GetGreen() const { return m_Green; }
		void SetGreen(float value);

		const float GetBlue() const { return m_Blue; }
		void SetBlue(float value);

		const float GetAlpha() const { return m_Alpha; }
		void SetAlpha(float value);

		void SetValues(float r, float g, float b, float a);

		static Color White();
		static Color Black();
		static Color Clear();
		static Color Red();
		static Color Green();
		static Color Blue();

		std::string ToString();
	};
}

