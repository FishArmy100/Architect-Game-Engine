#pragma once
#include "UpdateEntitySystem.h"
#include "Entity-Component-System/Entity.h"
#include "Entity-Component-System/Entity-Components/NativeScriptComponent.h"

namespace Architect
{
	class ScriptUpdateSystem : public UpdateEntitySystem
	{
	public:
		ScriptUpdateSystem();
		void OnAttach() override;

		void OnUpdate(std::shared_ptr<Scene> scene, float timestep) override;
		void OnScriptDestroyed(NativeScriptComponent& nsc);
	};
}

