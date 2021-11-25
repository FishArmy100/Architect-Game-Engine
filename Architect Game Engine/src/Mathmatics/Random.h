#pragma once

namespace Architect
{
	using uint32_t = unsigned int;

	class Random
	{
	public:
		Random(uint32_t seed);
		uint32_t Step();
		int Step(int min, int max);

	private:
		uint32_t State;
		uint32_t lcg_parkmiller(uint32_t seed);
	};
}

