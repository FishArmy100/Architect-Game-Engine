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
		NativeScriptInstance* m_ScriptInstance = nullptr;

	public:

		template<typename T>
		void Bind()
		{
			if (m_ScriptInstance != nullptr)
			{
				if(m_ScriptInstance->NativeScript != nullptr)
					m_ScriptInstance->NativeScript->OnDestroy();

				delete m_ScriptInstance;
			}

			m_ScriptInstance = new NativeScriptInstance();
			m_ScriptInstance->Bind<T>();
		}

		NativeScriptInstance* GetScriptInstance() { return m_ScriptInstance; }

		void OnDestroy()
		{
			m_ScriptInstance->NativeScript->OnDestroy();
			delete m_ScriptInstance;
		}
	};
}