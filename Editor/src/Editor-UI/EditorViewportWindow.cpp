#include "EditorViewportWindow.h"
#include "Entity-Component-System/SceneManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Application.h"
#include "User-Input/Input.h"
#include "Editor-Utils/EditorSelection.h"
#include "Entity-Component-System/Entity.h"
#include "Entity-Component-System/Entity-Systems/EntitySystems.h"
#include "imguizmo/ImGuizmo.h"
#include "Mathmatics/Math.h"
#include "Entity-Component-System/HierarchyUtils.h"
#include "Editor-Utils/EditorSettings.h"

namespace Editor
{
	EditorViewportWindow::EditorViewportWindow() 
		: EditorWindow("Viewport"), m_EditorCamera(glm::vec2(0), 0.3f, 8.0f, 2)
	{
		ImGuiWindowFlags windowFlags = 0;
		windowFlags |= ImGuiWindowFlags_NoCollapse;
		windowFlags |= ImGuiWindowFlags_MenuBar;

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

		m_EditorCamera.GetCamera().SetAspectRatio(wsize.x / wsize.y);

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

	void EditorViewportWindow::DrawGizmos()
	{
		if (!EditorSelection::HasSelection())
			return;

		Entity selectedEntity = EditorSelection::GetCurrentSelection()->GetEntity();
		if (selectedEntity)
		{
			ImGuizmo::SetOrthographic(true);
			ImGuizmo::SetDrawlist();

			glm::vec2 windowPosition = GetWindowPosition();
			glm::vec2 windowSize = GetWindowSize();

			ImGuizmo::SetRect(windowPosition.x, windowPosition.y, windowSize.x, windowSize.y);

			glm::mat4 cameraProjection = m_EditorCamera.GetCamera().GetProjectionMatrix();
			glm::mat4 cameraView = glm::inverse(m_EditorCamera.GetTransformMatrix());

			// Entity transform
			TransformComponent& tc = selectedEntity.GetComponent<TransformComponent>();
			glm::mat4 transformMat = Math::CalculateTransformMat(tc.Position, tc.Rotation, tc.Scale);

			if (selectedEntity.GetHasParent())
				transformMat = HierarchyUtils::LocalToWorld(selectedEntity.GetScene(), selectedEntity.GetParentID(), transformMat);

			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
				ImGuizmo::OPERATION::UNIVERSAL, ImGuizmo::MODE::LOCAL, glm::value_ptr(transformMat));

			if(selectedEntity.GetHasParent())
				transformMat = HierarchyUtils::WorldToLocal(selectedEntity.GetScene(), selectedEntity.GetParentID(), transformMat);

			if (ImGuizmo::IsUsing())
			{
				glm::vec3 position{0}, rotation{0}, scale{0};
				Math::DecomposeTransformMatrix(transformMat, position, rotation, scale);

				glm::vec3 deltaRotation = rotation - tc.Rotation;
				tc.Position = position;
				tc.Rotation += deltaRotation;
				tc.Scale = scale;
			}
		}

	}

	void EditorViewportWindow::OnRenderWindow()
	{
		std::string currentEditMode = EditorSettings::GetSettings().Mode == EditorMode::Play ? "Play" : "Edit";
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu(("Editor Mode: " + currentEditMode).c_str()))
			{
				if (ImGui::MenuItem("Play"))
					EditorSettings::GetSettings().Mode = EditorMode::Play;

				if (ImGui::MenuItem("Edit"))
					EditorSettings::GetSettings().Mode = EditorMode::Edit;

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}


		unsigned int textureID = m_FrameBuffer->GetColorAttachmentID(0);
		ImVec2 wsize = ImGui::GetContentRegionAvail();
		ImGui::Image((ImTextureID)textureID, wsize, ImVec2(0, 1), ImVec2(1, 0));
		DrawGizmos();
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