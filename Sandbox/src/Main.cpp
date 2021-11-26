#include "Architect.h"

using namespace Architect;

Random rng = Random(1);

void OnUpdate()
{
	if (Input::GetMouseButtonDown(MouseButtonCode::Right))
		Debug::Log("Test");
}

int main()
{
	Architect::Init(OnUpdate);
	return 0;
}