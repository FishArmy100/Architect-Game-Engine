#pragma once
#include "Layer.h"
#include "Rendering-System/Rendering.h"
#include "Entity-Component-System/Entity.h"
#include "GUI/ExampleWindow.h"

namespace Architect
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer() : Layer("Editor Layer") {}

	protected:
		void OnAttach() override;
		void OnUpdate(float timestep) override;
		void OnImGuiRender() override;
		void OnActiveSceneChanged(Scene* scene) override;

	private:
		Entity m_CameraEntity;
		UI::ExampleWindow* m_ExampleWindow;

		void TestMethod()
		{
			ARC_ENGINE_WARNING("Event Worked");
		}
	};
}

