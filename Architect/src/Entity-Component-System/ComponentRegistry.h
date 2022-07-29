#pragma once
#include <vector>
#include "RefLib/Types/Type.h"
#include "RefLib/Variant/Variant.h"
#include "Entity.h"
#include "RefLib/Instance/Instance.h"

namespace Architect
{
	struct RegisteredComponent
	{
		RefLib::TypeId ComponentType;
		std::function<bool(Entity)> HasComponent;
		std::function<void(Entity, const RefLib::Variant&)> AddComponent;
		std::function<RefLib::Instance(Entity)> GetComponent;
	};

	class ComponentRegistry
	{
	public:
		template<typename T>
		static void RegisterComponent()
		{
			static_assert(std::is_copy_constructible_v<T>, "T must be copy constructable");
			RegisteredComponent c;
			c.ComponentType = RefLib::Type::Get<T>();
			c.HasComponent = [](Entity e) { return e.ContainsComponent<T>(); };
			c.GetComponent = [](Entity e) -> RefLib::Instance { return e.GetComponent<T>(); };
			c.AddComponent = [](Entity e, const RefLib::Variant& v) { e.AddComponent<T>(v.TryConvert<T>().value()); };
		}

		static const std::vector<RegisteredComponent>& GetRegisteredComponents() { return s_RegisteredComponents; }

	private:
		inline static std::vector<RegisteredComponent> s_RegisteredComponents = {};
	};
}

#define ARC_REGISTER_COMPONENT(component) Architect::ComponentRegistry::RegisterComponent<component>();

