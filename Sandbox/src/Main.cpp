#include "Architect.h"

using namespace Architect;

Random rng = Random(1);

void OnUpdate()
{
	ullInt uuid = UUID::NewUUID();
	std::string uuidString = std::to_string(uuid);
	Debug::Log(uuidString);
}


int main()
{
	Architect::Init(OnUpdate);
	return 0;
}