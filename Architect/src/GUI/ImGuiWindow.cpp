#include "ImGuiWindow.h"
#include <iterator>
#include "Core.h"

namespace Architect
{
	namespace UI
	{
		int ImGuiWindow::s_CurrentWindowId = 0;

		ImGuiWindow::ImGuiWindow(const std::string& title, ImGuiWindowFlags flags)
			: m_Title(title), m_WindowFlags(flags), m_IsOpen(true), m_WindowId(s_CurrentWindowId),
			  m_WindowPosition(glm::vec2(0)), m_WindowSize(glm::vec2(0))
		{
			s_CurrentWindowId++;
		}

		void ImGuiWindow::RenderWindow(float timestep)
		{
			if (!m_IsOpen)
			{
				m_WindowSize = glm::vec2(0, 0);
				return;
			}

			OnBeginRenderWindow();

			ImGui::Begin(GetFullTitle().c_str(), &m_IsOpen, m_WindowFlags);

			UpdateSizeAndPosition();
			OnRenderWindow(timestep);

			ImGui::End();

			OnEndRenderWindow(); 

			if (!m_IsOpen)
			{
				const ImGuiWindow* guiWindow = this;
				m_WindowClosed.Invoke(guiWindow);
				OnWindowClosedAfterEvents();
			}
		}

		bool ImGuiWindow::GetMousePositionInWindow(glm::vec2* mousePosition)
		{
			auto [mx, my] = ImGui::GetMousePos();
			mx -= m_WindowPosition.x;
			my -= m_WindowPosition.y;

			my = m_WindowSize.y - my;
			int mouseX = (int)mx;
			int mouseY = (int)my;

			if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)m_WindowSize.x && mouseY < (int)m_WindowSize.y)
			{
				*mousePosition = { (float)mx, (float)my };
				return true;
			}

			*mousePosition = glm::vec2(0);
			return false;
		}

		glm::vec2 ImGuiWindow::CalculateWindowSize()
		{
			auto viewportMinRegion = ImVec2(0, 0); //ImGui::GetWindowContentRegionMin(); -> no idea what this does
			auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
			auto viewportOffset = ImGui::GetWindowPos();

			glm::vec2 viewportBounds[2]{};
			viewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
			viewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

			return viewportBounds[1] - viewportBounds[0];
		}

		const std::string ImGuiWindow::GetFullTitle()
		{
			return m_Title + std::string("##") + std::to_string(m_WindowId);
		}

		void ImGuiWindow::UpdateSizeAndPosition()
		{
			m_WindowSize = CalculateWindowSize();
			auto windowPos = ImGui::GetWindowPos();
			m_WindowPosition = { windowPos.x, windowPos.y };
		}
	}
}