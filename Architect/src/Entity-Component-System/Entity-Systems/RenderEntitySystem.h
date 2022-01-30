#pragma once
#include "Entity-Component-System/Scene.h"

namespace Architect
{
	class RenderEntitySystem
	{
	public:
		RenderEntitySystem(std::string name) : m_Name(name) {}
		virtual ~RenderEntitySystem() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnRender(std::shared_ptr<Scene> scene) = 0;
		const std::string& GetName() { return m_Name; }

	private:
		std::string m_Name;
	};
}

