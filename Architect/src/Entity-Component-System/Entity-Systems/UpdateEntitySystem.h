#pragma once
#include "Entity-Component-System/Scene.h"

namespace Architect
{
	class UpdateEntitySystem
	{
	public:
		UpdateEntitySystem(std::string name) : m_Name(name) {}
		virtual ~UpdateEntitySystem() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(std::shared_ptr<Scene> scene, float timestep) = 0;

		const std::string& GetName() { return m_Name; }

	private:
		std::string& m_Name;
	};
}

