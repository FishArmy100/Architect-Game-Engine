#include "Architect.h"

void OnUpdate()
{
	if(Architect::Input::GetKeyDown(Architect::KeyCode::A))
		Architect::Debug::Log("Hello World");
}

int main()
{
	Architect::Init(OnUpdate);
	return 0;
}