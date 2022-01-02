#include "ImGuiWindow.h"
#include <iterator>

namespace Architect
{
	namespace UI
	{
		ImGuiWindow::ImGuiWindow(const std::string& title) : m_Title(title)
		{
			
		}

		ImGuiWindow::~ImGuiWindow()
		{

		}

		void ImGuiWindow::RenderWindow()
		{
			ImGui::Begin(m_Title.c_str());
			OnRenderWindow();
			ImGui::End();
		}
	}
}