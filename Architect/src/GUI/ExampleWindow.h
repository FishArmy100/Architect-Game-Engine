#pragma once
#include "ImGuiWindow.h"

namespace Architect
{
	namespace UI
	{
		class ExampleWindow : public ImGuiWindow
		{
		public:
			ExampleWindow(const std::string& title);

		protected:
			void OnRenderWindow() override;

		private:
			float testFloat;
			Color testColor;
		};
	}
}

