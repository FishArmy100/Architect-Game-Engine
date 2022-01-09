#pragma once
#include "Core/Layer.h"
#include "Rendering-System/Rendering.h"
#include "Entity-Component-System/Entity.h"
#include "GUI/ExampleWindow.h"
#include "Editor-UI/EditorViewportWindow.h"

namespace Editor
{
	using namespace Architect;

	class EditorLayer : public Layer
	{
	public:
		EditorLayer() : Layer("Editor Layer") {}

	protected:
		void OnAttach() override;
		void OnUpdate(float timestep) override;
		void OnImGuiRender(float timestep) override;
		bool OnEvent(IApplicationEvent* appEvent);
		void OnActiveSceneChanged(std::shared_ptr<Scene> scene) override;

	private:
		void DrawMainMenu();
		void DrawDockSpace();

	private:
		Entity m_CameraEntity;
	};
}

