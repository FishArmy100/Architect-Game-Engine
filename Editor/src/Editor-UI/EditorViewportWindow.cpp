#include "EditorViewportWindow.h"
#include "Entity-Component-System/SceneRenderer.h"
#include "Entity-Component-System/SceneManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Application.h"
#include "User-Input/Input.h"
#include "Editor-Utils/EditorSelection.h"
#include "Entity-Component-System/Entity.h"

namespace Editor
{
	EditorViewportWindow::EditorViewportWindow() 
		: EditorWindow("Viewport"), m_EditorCamera(glm::vec2(0), 0.3f, 8.0f, 2)
	{
		ImGuiWindowFlags windowFlags = 0;
		windowFlags |= ImGuiWindowFlags_NoCollapse;

		SetFlags(windowFlags);
		FramebufferSpecification spec;
		spec.Attachments = { FbTexAttachFormat::RGBA8, FbTexAttachFormat::RED_INTEGER, FbTexAttachFormat::DEPTH24STENCIL8 };
		spec.Width = 1;
		spec.Height = 1;
		m_FrameBuffer = std::make_shared<Framebuffer>(spec);
	}

	// code must be in own method, otherwise werid ImGui graphical glitch, possibly openGL?
	void EditorViewportWindow::HandleEntitySelection()
	{
		glm::vec2 mousePos;
		if (Input::GetMouseButtonDown(MouseButtonCode::Left) && GetMousePositionInWindow(&mousePos)) 
		{
			int entityId = m_FrameBuffer->ReadColorPixel(1, (int)mousePos.x, (int)mousePos.y);
			if (entityId != -1) 
			{
				Entity e = Entity((entt::entity)entityId, SceneManager::GetActiveScene().get()); 
				std::shared_ptr<EditorSelection> selection = std::make_shared<EditorSelection>(e); 
				EditorSelection::SetCurrentSelection(selection); 
			}
			else
			{
				EditorSelection::SetCurrentSelection(nullptr);
			}
		}
	}

	void EditorViewportWindow::UpdateFramebuffer()
	{
		glm::vec2 wsize = GetWindowSize();

		if (wsize.x < 1 || wsize.y < 1)
			return;

		const FramebufferSpecification spec = m_FrameBuffer->GetSpecification();

		m_FrameBuffer->ClearColorAttachment(0, 0);
		m_FrameBuffer->ClearColorAttachment(1, -1);

		if (spec.Width != wsize.x || spec.Height != wsize.y)
			m_FrameBuffer->Resize((unsigned int)wsize.x, (unsigned int)wsize.y);

		m_EditorCamera.GetCamera()->SetAspectRatio(wsize.x / wsize.y);

		glm::mat4 cameraTransform = m_EditorCamera.GetTransformMatrix();

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		Renderer::Begin(m_EditorCamera.GetCamera(), cameraTransform, m_FrameBuffer);
		SceneRenderer::RenderScene(SceneManager::GetActiveScene());
		Renderer::End();
	}

	void EditorViewportWindow::OnRenderWindow(float timestep)
	{
		glm::vec2 mousePos;
		if (GetMousePositionInWindow(&mousePos) && ImGui::IsWindowFocused())
		{
			m_EditorCamera.Update(timestep, mousePos);
		}

		unsigned int textureID = m_FrameBuffer->GetColorAttachmentID(0);
		ImVec2 wsize = ImGui::GetContentRegionAvail();
		ImGui::Image((ImTextureID)textureID, wsize, ImVec2(0, 1), ImVec2(1, 0));
	}

	void EditorViewportWindow::OnBeginRenderWindow()
	{
		UpdateFramebuffer();
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	}

	void EditorViewportWindow::OnEndRenderWindow()
	{
		ImGui::PopStyleVar();
		HandleEntitySelection();
	}
}