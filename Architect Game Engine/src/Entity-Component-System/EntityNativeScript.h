#pragma once
#include "Entity.h"

namespace Architect
{
	struct NativeScriptInstance;

	class EntityNativeScript
	{
	private:
		Entity m_Entity;
		friend struct NativeScriptInstance;

	public:
		virtual void OnCreate() {}
		virtual void OnUpdate(float timeStep) {}
		virtual void OnDestroy() {}

	public:
		Entity& GetEntity() { return m_Entity; }

		template<typename T>
		bool ContainsComponent()
		{
			return m_Entity.ContainsComponent<T>();
		}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return m_Entity.AddComponent<T>(std::forward<Args>(args));
		}

		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

		template<typename T>
		bool TryGetComponent(T*& outComponent)
		{
			if (ContainsComponent<T>())
			{
				outComponent = &GetComponent<T>();

			}

			outComponent = nullptr;
			return false;
		}
	};
}

