#include "EditorViewportWindow.h"
#include "Entity-Component-System/SceneRenderer.h"
#include "Entity-Component-System/SceneManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Application.h"

namespace Editor
{
	EditorViewportWindow::EditorViewportWindow() 
		: EditorWindow("Viewport"), m_EditorCamera(glm::vec2(0), 0.3f, 8.0f, 2)
	{
		ImGuiWindowFlags windowFlags = 0;
		windowFlags |= ImGuiWindowFlags_NoCollapse;

		SetFlags(windowFlags);
		FramebufferSpecification spec;
		spec.Width = 1;
		spec.Height = 1;
		m_FrameBuffer = std::make_shared<Framebuffer>(spec);
	}

	void EditorViewportWindow::OnRenderWindow(float timestep)
	{
		glm::vec2 mousePos;
		if (GetMousePositionInWindow(&mousePos) && ImGui::IsWindowFocused())
		{
			m_EditorCamera.Update(timestep, mousePos);
		}

		unsigned int textureID = m_FrameBuffer->GetColorAttachmentID();
		ImVec2 wsize = ImGui::GetContentRegionAvail();

		m_FrameBuffer->Resize((unsigned int)wsize.x, (unsigned int)wsize.y);

		m_EditorCamera.GetCamera()->SetAspectRatio(wsize.x / wsize.y);

		glm::mat4 cameraTransform = m_EditorCamera.GetTransformMatrix();

		Renderer::Begin(m_EditorCamera.GetCamera(), cameraTransform, m_FrameBuffer);
		SceneRenderer::RenderScene(SceneManager::GetActiveScene());
		Renderer::End();

		ImGui::Image((ImTextureID)textureID, wsize, ImVec2(0, 1), ImVec2(1, 0));
	}

	void EditorViewportWindow::OnBeginRenderWindow()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	}

	void EditorViewportWindow::OnEndRenderWindow()
	{
		ImGui::PopStyleVar();
	}
}