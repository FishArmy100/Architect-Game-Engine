#include "ScriptUpdator.h"
#include "Entity.h"
#include "NativeScriptInstance.h"

namespace Architect
{
	void ScriptUpdator::UpdateScripts(std::shared_ptr<Scene> scene, float timestep)
	{
		scene->GetEntitiesWithComponent<NativeScriptComponent>([=](Entity& e, NativeScriptComponent& nsc)
		{
			if (nsc.GetScriptInstance()->NativeScript == nullptr)
			{
				nsc.GetScriptInstance()->CreateScriptInstanceFunction(e);
				nsc.GetScriptInstance()->NativeScript->OnCreate();
			}
			else
			{
				nsc.GetScriptInstance()->NativeScript->OnUpdate(timestep);
			}
		});
	}

	void ScriptUpdator::OnScriptDestroyed(NativeScriptComponent& component)
	{
		component.GetScriptInstance()->NativeScript->OnDestroy();
		component.GetScriptInstance()->DestroyScriptInstanceFunciton();
	}
}