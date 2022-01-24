#include "HierarchyWindow.h"
#include "Entity-Component-System/SceneManager.h"
#include "Entity-Component-System/Entity.h"
#include <glm/gtc/type_ptr.hpp>
#include "Editor-Utils/EditorSelection.h"
#include <memory>

namespace Editor
{
	HierarchyWindow::HierarchyWindow() : EditorWindow("Hierarchy")
	{

	}

	void HierarchyWindow::OnRenderWindow()
	{
		std::shared_ptr<Scene> scene = SceneManager::GetActiveScene();

		std::function<void(Entity&, EntityDataComponent&)> renderEntityHierarchyFunc = [=](Entity& e, EntityDataComponent& entityData)
		{
			DrawEntity(e);
		};

		scene->GetEntitiesWithComponent<EntityDataComponent>(renderEntityHierarchyFunc);
	}

	void HierarchyWindow::DrawEntity(Entity e)
	{
		if (m_DrawnEntities.find((uint32_t)(EntityID)e) != m_DrawnEntities.end())
			return;

		m_DrawnEntities.emplace((uint32_t)e);

		bool isEntitySelected = EditorSelection::HasSelection(EditorSelection(e));

		ImGuiTreeNodeFlags flags = ((isEntitySelected) ? ImGuiTreeNodeFlags_Selected : 0);
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

		bool isOpened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)e, flags, e.GetName().c_str());

		if (ImGui::IsItemClicked() && !isEntitySelected)
			EditorSelection::SetCurrentSelection(std::make_shared<EditorSelection>(e));

		if (isOpened)
		{
			for (Entity& child : e.GetChildren())
				DrawEntity(child);

			ImGui::TreePop();
		}
	}
}