#pragma once
#include <random>
#include <memory>

using ullInt = unsigned long long int;

namespace Architect
{
	class UUID
	{
	public:
		static ullInt NewUUID();

	private:
		static std::shared_ptr<std::mt19937_64> MersenneTwister;
	};
}


