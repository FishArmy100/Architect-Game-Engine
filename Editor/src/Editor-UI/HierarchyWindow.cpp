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

	void HierarchyWindow::OnRenderWindow(float timestep)
	{
		std::shared_ptr<Scene> scene = SceneManager::GetActiveScene();
		scene->GetEntitiesWithComponent<EntityDataComponent>([=](Entity& e, EntityDataComponent& entityData)
		{
			bool isEntitySelected = EditorSelection::HasSelection(EditorSelection(e));

			ImGuiTreeNodeFlags flags = ((isEntitySelected) ? ImGuiTreeNodeFlags_Selected : 0);
			flags |= ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow;

			bool isOpened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)e, flags, entityData.Name.c_str());

			if (ImGui::IsItemClicked() && !isEntitySelected)
				EditorSelection::SetCurrentSelection(std::make_shared<EditorSelection>(e));

			if (isOpened)
				ImGui::TreePop();
		});
	}
}