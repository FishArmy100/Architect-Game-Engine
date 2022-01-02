#pragma once
#include <string>
#include "../Mathmatics/Color.h"
#include "imgui/imgui.h"

namespace Architect
{
	namespace UI
	{
		class ImGuiWindow
		{
		private:
			std::string m_Title;

		public:
			ImGuiWindow(const std::string& title = "Window");
			~ImGuiWindow();

			void RenderWindow();
			const std::string GetName() const { return m_Title; }

		protected:
			virtual void OnRenderWindow() = 0;
		};
	}
}

