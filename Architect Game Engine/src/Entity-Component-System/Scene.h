#pragma once
#include <string>
#include "entt/entt.hpp"

namespace Architect
{
	class Entity;
	class EntitySystem;

	class Scene
	{
	private:
		unsigned long long int m_SceneID;
		std::string m_Name;
		entt::registry m_EntityRegistry;

		friend class Entity;
		friend class EntitySystem;

	public:
		Scene(const std::string& name = "Scene");

		unsigned long long int GetID() { return m_SceneID; }

		std::string GetName() { return m_Name; }

		Entity CreateEntity(const std::string& name);
	};
}

