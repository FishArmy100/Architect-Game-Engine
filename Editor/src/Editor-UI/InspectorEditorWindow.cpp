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

		ImGui::Checkbox("Is Active", &e.GetComponent<IsActiveComponent>().IsActive);
		ImGui::InputText("Tag", &e.GetComponent<TagComponent>().Tag);

		TransformComponent& transform = e.GetTransform();
		glm::vec3 position = transform.GetPosition();
		glm::vec3 rotation = transform.GetRotation();
		glm::vec3 scale = transform.GetScale(); 

		UI::ImGuiHelper::Vector3Input("Position", &position);
		UI::ImGuiHelper::Vector3Input("Rotation", &rotation);
		UI::ImGuiHelper::Vector3Input("Scale", &scale);

		transform.SetPosition(position);
		transform.SetRotation(rotation);
		transform.SetScale(scale);
	}
}