#include "ScriptUpdateSystem.h"

namespace Architect
{
	void ScriptUpdateSystem::OnUpdate(float timeStep)
	{
		GetEntitiesWithComponent<NativeScriptComponent>([&](Entity& e, NativeScriptComponent& nsc)
		{
			OnEntity(e, nsc, timeStep);
		}); 
	}

	void ScriptUpdateSystem::OnStart()
	{
		m_OnScriptComponentDestroyedLisener = AddLisenerToOnComponentDestroyed<NativeScriptComponent>([](NativeScriptComponent& scriptComponent)
		{
			scriptComponent.OnDestroy();
		});
	}

	void ScriptUpdateSystem::OnStop()
	{
		RemoveLisenerFromOnComponentDestroyed(m_OnScriptComponentDestroyedLisener);
	}

	void ScriptUpdateSystem::OnEntity(Entity& e, NativeScriptComponent& nsc, float timeStep)
	{
		NativeScriptInstance* scriptInstance = nsc.GetScriptInstance();

		if (!(*scriptInstance))
		{
			scriptInstance->CreateScriptInstanceFunction(e);
			scriptInstance->NativeScript->OnCreate();
		}
		else
		{
			scriptInstance->NativeScript->OnUpdate(timeStep);
		}
	}
}