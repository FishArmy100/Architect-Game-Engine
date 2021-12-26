#include "ExampleWindow.h"
#include "../Logger/Logger.h"

namespace Architect
{
	namespace UI
	{
		ExampleWindow::ExampleWindow(const std::string& title) : testFloat(0), GUIWindow(title)
		{
			testColor = Color::White();
		}

		void ExampleWindow::OnRenderWindow()
		{
			Text("Example Text");
			FloatInput("Example Float", &testFloat);
			ColorInput("Example Color", &testColor);
			std::string colorString = testColor.ToString();
			ARC_ENGINE_INFO(colorString);
		}
	}
}