#include "ExampleWindow.h"
#include "../Logger/Logger.h"
#include "ImGuiHelper.h"

namespace Architect
{
	namespace UI
	{
		ExampleWindow::ExampleWindow(const std::string& title) : testFloat(0), ImGuiWindow(title)
		{
			testColor = Color::White();
		}

		void ExampleWindow::OnRenderWindow(float timestep)
		{
			ImGui::Text("Example Text");
			ImGui::InputFloat("Example Float", &testFloat);
			ImGuiHelper::ColorInput("Example Color", &testColor);
			std::string colorString = testColor.ToString();
			//ARC_ENGINE_INFO(colorString);
		}
	}
}