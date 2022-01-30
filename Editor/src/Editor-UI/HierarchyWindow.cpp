#include "HierarchyWindow.h"
#include "Entity-Component-System/SceneManager.h"
#include "Entity-Component-System/Entity.h"
#include <glm/gtc/type_ptr.hpp>
#include "Editor-Utils/EditorSelection.h"
#include "Entity-Component-System/HierarchyUtils.h"
#include <memory>

namespace Editor
{
	HierarchyWindow::HierarchyWindow() : EditorWindow("Hierarchy", ImGuiWindowFlags_MenuBar)
	{

	}

	void HierarchyWindow::OnRenderWindow()
	{
		std::shared_ptr<Scene> scene = SceneManager::GetActiveScene();

		m_DrawnEntities.clear();

		if(ImGui::BeginMenuBar())
		{
			std::string editTypeString = "Current Edit Type: ";
			editTypeString += m_EditType == HierarchyEditType::Parenting ? "Parenting" : "Ordering";

			if (ImGui::BeginMenu(editTypeString.c_str()))
			{
				if (ImGui::MenuItem("Edit Entity Parents/Childern"))
					m_EditType = HierarchyEditType::Parenting;

				if (ImGui::MenuItem("Edit Entity Order"))
					m_EditType = HierarchyEditType::Ordering;

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		for(int i = 0; i < scene->GetEntityCount(); i++)
		{
			EntityID id = (*scene)[i].value();

			if(scene->GetComponentFromEntity<HierarchyComponent>(id).Parent == NullEntity)
				DrawEntity(Entity(id, scene.get()));
		}

		ImGui::Dummy(ImGui::GetContentRegionAvail());

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("HIERARCHY_ENTITY"))
			{
				Entity selectedEntity = EditorSelection::GetCurrentSelection()->GetEntity();

				if (selectedEntity.GetHasParent())
					HierarchyUtils::ClearParent(selectedEntity.GetScene(), (EntityID)selectedEntity);
			}
			ImGui::EndDragDropTarget();
		}

		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			ShowEntityPopupMenu();
		}
		DrawEntityPopupMenu();
	}

	void HierarchyWindow::DrawEntityPopupMenu()
	{
		if (ImGui::BeginPopup("Entity Select Popup"))
		{
			ImGui::Text("Entity Options:");
			ImGui::Separator();

			if (ImGui::Selectable("Create Empty"))
			{
				SceneManager::GetActiveScene()->CreateEntity("Entity");
			}

			if (ImGui::Selectable("Delete Selected"))
			{
				if (EditorSelection::HasSelection())
				{
					Entity e = EditorSelection::GetCurrentSelection()->GetEntity();
					e.GetScene()->DestoryEntity(e);
					EditorSelection::SetCurrentSelection(nullptr);
				}
			}

			ImGui::EndPopup();
		}
	}

	void HierarchyWindow::ShowEntityPopupMenu()
	{
		ImGui::OpenPopup("Entity Select Popup");
	}

	void HierarchyWindow::DrawEntity(Entity e)
	{
		if (m_DrawnEntities.find((uint32_t)(EntityID)e) != m_DrawnEntities.end())
			return;

		m_DrawnEntities.emplace((uint32_t)(EntityID)e); 

		ImGui::PushID((int)(EntityID)e);

		ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
		
		EditorSelection selection = EditorSelection(e);
		if (EditorSelection::HasSelection(selection))
			nodeFlags |= ImGuiTreeNodeFlags_Selected;

		nodeFlags |= e.GetChildrenIDs().size() > 0 ? 0 : ImGuiTreeNodeFlags_Bullet;

		bool nodeOpen = ImGui::TreeNodeEx(e.GetName().c_str(), nodeFlags);

		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			ShowEntityPopupMenu();
		}
		DrawEntityPopupMenu();

		HandleDragDrop(e);

		if (ImGui::IsItemClicked())
			EditorSelection::SetCurrentSelection(std::make_shared<EditorSelection>(e));

		if (nodeOpen)
		{
			for (Entity child : e.GetChildren())
				DrawEntity(child);

			ImGui::TreePop();
		}

		ImGui::PopID();
	}

	void HierarchyWindow::HandleDragDrop(Entity e)
	{
		if (ImGui::BeginDragDropSource())
		{
			int unused = 0;
			ImGui::SetDragDropPayload("HIERARCHY_ENTITY", &unused, sizeof(int));
			EditorSelection::SetCurrentSelection(std::make_shared<EditorSelection>(e));
			ImGui::EndDragDropSource();
		}

		if (ImGui::BeginDragDropTarget())
		{
			Entity selectedEntity = EditorSelection::GetCurrentSelection()->GetEntity();

			bool isEValidParent = !HierarchyUtils::ContainsDecedent(e.GetScene(), (EntityID)selectedEntity, (EntityID)e);
			const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("HIERARCHY_ENTITY");

			Scene* scene = e.GetScene();

			if (payload && isEValidParent && m_EditType == HierarchyEditType::Parenting)
			{
				if (selectedEntity.GetHasParent())
					HierarchyUtils::ClearParent(scene, (EntityID)selectedEntity);

				HierarchyUtils::SetParent(scene, (EntityID)selectedEntity, (EntityID)e);
			}

			if (payload && m_EditType == HierarchyEditType::Ordering)
			{
				auto entityIndex = scene->IndexOf(e).value();
				auto selectedEntityIndex = scene->IndexOf(selectedEntity).value();
				scene->MoveEntity(selectedEntityIndex, entityIndex);
			}

			ImGui::EndDragDropTarget();
		}
	}
}