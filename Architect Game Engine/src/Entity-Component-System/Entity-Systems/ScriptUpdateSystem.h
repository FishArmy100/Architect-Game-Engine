#pragma once
#include "Entity-Component-System/EntitySystem.h"
#include "Entity-Component-System/Entity-Components/NativeScriptComponent.h"

namespace Architect
{
	class ScriptUpdateSystem : public EntitySystem
	{
	protected:
		void OnUpdate(float timeStep) override;
		void OnStart() override;
		void OnStop() override;

	private:
		void OnEntity(Entity& e, NativeScriptComponent& nsc, float timeStep);
		OnDestoryComponentLisener<NativeScriptComponent>* m_OnScriptComponentDestroyedLisener;
	};
}

