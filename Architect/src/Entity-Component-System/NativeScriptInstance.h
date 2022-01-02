#pragma once
#include "EntityNativeScript.h"
#include <functional>
#include "Core.h"


namespace Architect
{
	struct NativeScriptInstance
	{
		EntityNativeScript* NativeScript = nullptr;

		~NativeScriptInstance()
		{
			if(NativeScript != nullptr)
				DestroyScriptInstanceFunciton();

			ARC_ENGINE_WARNING("Script Instace Destroid");
		}

		std::function<void(Entity)> CreateScriptInstanceFunction;
		std::function<void()> DestroyScriptInstanceFunciton;

		inline bool operator== (const NativeScriptInstance& rhs) const
		{
			return NativeScript == rhs.NativeScript;
		}

		operator bool() const { return NativeScript != nullptr; }

		template<typename T>
		void Bind()
		{
			CreateScriptInstanceFunction = [&](Entity e)
			{
				NativeScript = new T();
				NativeScript->m_Entity = e;
			};

			DestroyScriptInstanceFunciton = [&]()
			{
				delete (T*)NativeScript; 
				NativeScript = nullptr;
			};
		}
	};
}