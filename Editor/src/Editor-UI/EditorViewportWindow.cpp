#include "EditorViewportWindow.h"
#include "Entity-Component-System/SceneManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Application.h"
#include "User-Input/Input.h"
#include "Editor-Utils/EditorSelection.h"
#include "Entity-Component-System/Entity.h"
#include "Entity-Component-System/Entity-Systems/EntitySystems.h"

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

		m_FrameBuffer->Clear();
		m_FrameBuffer->ClearColorAttachment(1, -1);

		if (spec.Width != wsize.x || spec.Height != wsize.y)
			m_FrameBuffer->Resize((unsigned int)wsize.x, (unsigned int)wsize.y);

		m_EditorCamera.GetCamera()->SetAspectRatio(wsize.x / wsize.y);

		glm::mat4 cameraTransform = m_EditorCamera.GetTransformMatrix();
	}

	void EditorViewportWindow::UpdateCamera(float timestep)
	{
		glm::vec2 mousePos;
		if (GetMousePositionInWindow(&mousePos) && GetIsSelected())
		{
			m_EditorCamera.Update(timestep, mousePos);
		}
	}

	void EditorViewportWindow::OnRenderWindow()
	{
		unsigned int textureID = m_FrameBuffer->GetColorAttachmentID(0);
		ImVec2 wsize = ImGui::GetContentRegionAvail();
		ImGui::Image((ImTextureID)textureID, wsize, ImVec2(0, 1), ImVec2(1, 0));
	}

	void EditorViewportWindow::UpdateWindow(float timestep)
	{
		UpdateFramebuffer();
		EntitySystems::OnRender(SceneManager::GetActiveScene(), m_EditorCamera.GetCamera(), m_EditorCamera.GetTransformMatrix(), m_FrameBuffer);
		HandleEntitySelection();
		UpdateCamera(timestep);
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