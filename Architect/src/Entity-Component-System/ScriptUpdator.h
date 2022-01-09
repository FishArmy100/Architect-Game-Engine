#pragma once
#include "Scene.h"
#include "Entity-Components/NativeScriptComponent.h"

namespace Architect
{
	class ScriptUpdator
	{
	public:
		static void UpdateScripts(std::shared_ptr<Scene> scene, float timestep);
		static void OnScriptDestroyed(NativeScriptComponent& component);
	};
}

