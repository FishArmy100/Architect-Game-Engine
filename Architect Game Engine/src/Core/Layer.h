#pragma once
#include <string>
#include "Core.h"
#include "Entity-Component-System/Scene.h"
#include "IApplicationEvent.h"

namespace Architect
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float timestep) {}
		virtual bool OnEvent(IApplicationEvent* appEvent) { return false;  };
		virtual void OnImGuiRender() {}
		virtual void OnActiveSceneChanged(Scene* scene) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}

