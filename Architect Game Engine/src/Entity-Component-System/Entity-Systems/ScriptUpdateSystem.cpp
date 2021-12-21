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

	// Doesent work with multiple scripts on entity
	void ScriptUpdateSystem::OnEntity(Entity& e, NativeScriptComponent& nsc, float timeStep)
	{
		std::vector<NativeScriptInstance*> scriptInstances = nsc.GetScriptInstances();

		for (int i = 0; i < scriptInstances.size(); i++)
		{
			if (!(*scriptInstances[i]))
			{
				scriptInstances[i]->CreateScriptInstanceFunction(e);
				scriptInstances[i]->NativeScript->OnCreate();
			}
			else
			{
				scriptInstances[i]->NativeScript->OnUpdate(timeStep);
			}
		}
	}
}