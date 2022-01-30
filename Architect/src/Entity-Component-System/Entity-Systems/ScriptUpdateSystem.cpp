#include "ScriptUpdateSystem.h"
#include "Entity-Component-System/SceneManager.h"

namespace Architect
{
	ScriptUpdateSystem::ScriptUpdateSystem() : UpdateEntitySystem("Script Update System")
	{
	}

	void ScriptUpdateSystem::OnAttach()
	{
		// currently doesent work if swap scenes
		SceneManager::GetActiveScene()->AddLisenerToOnComponentDestroyed<NativeScriptComponent>([&](NativeScriptComponent& nsc)
		{
			OnScriptDestroyed(nsc);
		});
	}

	void ScriptUpdateSystem::OnUpdate(std::shared_ptr<Scene> scene, float timestep)
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

	void ScriptUpdateSystem::OnScriptDestroyed(NativeScriptComponent& nsc)
	{
		nsc.GetScriptInstance()->NativeScript->OnDestroy();
		nsc.GetScriptInstance()->DestroyScriptInstanceFunciton();
	}
}