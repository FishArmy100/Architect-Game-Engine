#include "HierarchyWindow.h"
#include "Entity-Component-System/SceneManager.h"
#include "Entity-Component-System/Entity.h"
#include <glm/gtc/type_ptr.hpp>

namespace Editor
{
	HierarchyWindow::HierarchyWindow() : EditorWindow("Hierarchy")
	{

	}

	void HierarchyWindow::OnRenderWindow(float timestep)
	{
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth;

		std::shared_ptr<Scene> scene = SceneManager::GetActiveScene();
		scene->GetEntitiesWithComponent<TagComponent>([=](Entity& e, TagComponent& tag)
		{
			bool isOpened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)e, flags, tag.Tag.c_str());

			if (isOpened)
			{
				ImGui::TreePop();
			}
		});
	}
}