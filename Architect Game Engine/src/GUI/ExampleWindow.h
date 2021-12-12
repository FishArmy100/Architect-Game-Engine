#pragma once
#include "GUIWindow.h"

namespace Architect
{
	namespace UI
	{
		class ExampleWindow : public GUIWindow
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

