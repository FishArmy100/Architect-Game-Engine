#pragma once
#include "EditorWindow.h"
#include "Rendering-System/Rendering.h"
#include "Rendering-System/Camera.h"
#include "Editor-Utils/EditorCamera.h"

namespace Editor
{
	using namespace Architect;

	class EditorViewportWindow : public EditorWindow
	{
	public:
		EditorViewportWindow();

	protected:
		void OnRenderWindow() override;
		void UpdateWindow(float timestep) override;
		void OnBeginRenderWindow() override;
		void OnEndRenderWindow() override;

	private:
		void HandleEntitySelection();
		void UpdateFramebuffer();
		void UpdateCamera(float timestep);
		void DrawGizmos();

	private:
		 std::shared_ptr<Framebuffer> m_FrameBuffer;
		 EditorCamera m_EditorCamera;
	}; 
}

