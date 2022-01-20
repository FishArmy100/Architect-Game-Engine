#include "InspectorEditorWindow.h"
#include "Editor-Utils/EditorSelection.h"
#include "imgui/imgui_stdlib.h"
#include "GUI/ImGuiHelper.h"

namespace Editor
{
	InspectorEditorWindow::InspectorEditorWindow() : EditorWindow("Inspector")
	{
	}

	void InspectorEditorWindow::OnRenderWindow(float timestep)
	{
		if (!EditorSelection::HasSelection())
		{
			ImGui::Text("No Entity Selected");
			return;
		}

		Entity e = EditorSelection::GetCurrentSelection()->GetEntity();

		ImGui::Checkbox("Is Active", &e.GetComponent<EntityDataComponent>().IsActive);
		ImGui::InputText("Name", &e.GetComponent<EntityDataComponent>().Name);

		TransformComponent& transform = e.GetTransform();
		UI::ImGuiHelper::Vector3Input("Position", &transform.Position);
		UI::ImGuiHelper::Vector3Input("Rotation", &transform.Rotation);
		UI::ImGuiHelper::Vector3Input("Scale", &transform.Scale);
	}
}