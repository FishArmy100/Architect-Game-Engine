#pragma once
#include "../Entity-Component-System/EntityNativeScript.h"
#include <functional>
#include "Entity-Component-System/NativeScriptInstance.h"
#include <vector>

#include "Core.h"

namespace Architect
{
	class NativeScriptComponent
	{
	private:
		std::vector<NativeScriptInstance*> m_ScriptInstances;

	public:

		template<typename T>
		void AddScript()
		{
			m_ScriptInstances.emplace_back(new NativeScriptInstance())->Bind<T>();
		}

		std::vector<NativeScriptInstance*>& GetScriptInstances() { return m_ScriptInstances; }

		void OnDestroy()
		{
			ARC_ENGINE_INFO("Destroyed Component");
		}

		/*~NativeScriptComponent()
		{
			for (auto instance : m_ScriptInstances)
			{
				if (instance->NativeScript)
				{
					instance->NativeScript->OnDestroy();
				}
			}
			for (auto instance : m_ScriptInstances)
			{
				delete instance;
			}
		}*/
	};
}