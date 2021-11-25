#include "Architect.h"

using namespace Architect;

Random rng = Random(1);

void OnUpdate()
{
	std::string str = std::to_string(rng.Step(-10, 5));
	Debug::Log(str);
}

int main()
{
	Architect::Init(OnUpdate);
	return 0;
}