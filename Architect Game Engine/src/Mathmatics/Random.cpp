#include "Random.h"

namespace Architect
{
	Random::Random(uint32_t seed)
	{
		State = seed;
		if (State == 0)
			State = 1;
	}

	uint32_t Random::Step()
	{
		State = lcg_parkmiller(State);
		return State;
	}

	int Random::Step(int min, int max)
	{
		if (min >= max)
			return 0;

		int difference = (max + 1) - min;
		uint32_t randomNumber = Step();

		int clampedNumber = randomNumber % difference;
		return clampedNumber + min;
	}

	// https://en.wikipedia.org/wiki/Lehmer_random_number_generator
	// To use only 32-bit arithmetic, use Schrage's method:
	uint32_t Random::lcg_parkmiller(uint32_t state)
	{
		// Precomputed parameters for Schrage's method
		const uint32_t M = 0x7fffffff;
		const uint32_t A = 48271;
		const uint32_t Q = M / A;    // 44488
		const uint32_t R = M % A;    //  3399

		uint32_t div = state / Q;	// max: M / Q = A = 48,271
		uint32_t rem = state % Q;	// max: Q - 1     = 44,487

		int s = rem * A;	// max: 44,487 * 48,271 = 2,147,431,977 = 0x7fff3629
		int t = div * R;	// max: 48,271 *  3,399 =   164,073,129
		int result = s - t;

		if (result < 0)
			result += M;

		return state = result;
	}
}