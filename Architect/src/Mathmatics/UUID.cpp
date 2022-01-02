#include "UUID.h"
#include <cmath>

namespace Architect
{
	std::shared_ptr<std::mt19937_64> UUID::MersenneTwister;

	ullInt UUID::NewUUID()
	{
		if (MersenneTwister == nullptr)
		{
			std::random_device rd;
			MersenneTwister = std::make_shared<std::mt19937_64>(rd());
		}

		return MersenneTwister->operator()();
	}
}