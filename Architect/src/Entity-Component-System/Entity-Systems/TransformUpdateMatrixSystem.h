#pragma once
#include "Entity-Component-System/Entity-Systems/UpdateEntitySystem.h"

namespace Architect
{
	class TransformUpdateMatrixSystem : public UpdateEntitySystem
	{
	public:
		TransformUpdateMatrixSystem();
		void OnUpdate(std::shared_ptr<Scene> scene, float timestep);
	};
}

