#pragma once
#include <string>
#include "../Mathmatics/Color.h"
#include "imgui/imgui.h"
#include "Core/Events.h"
#include "glm/vec2.hpp"

namespace Architect
{
	namespace UI
	{
		class ImGuiWindow
		{

		public:
			ImGuiWindow(const std::string& title = "Window", ImGuiWindowFlags flags = 0);
			virtual ~ImGuiWindow() = default;

			void RenderWindow(float timestep);
			const std::string& GetTitle() const { return m_Title; }
			void SetTitle(const std::string& title) { m_Title = title; }

			ImGuiWindowFlags GetFlags() const { return m_WindowFlags; }
			void SetFlags(ImGuiWindowFlags flags) { m_WindowFlags = flags; }

			EventHandler<const ImGuiWindow*>& GetWindowClosedEventHandler() { return m_WindowClosed; }

			bool GetIsOpen() const { return m_IsOpen; }
			bool SetIsOpen(bool isOpen) { m_IsOpen = isOpen; }

			glm::vec2 GetWindowSize() const { return m_WindowSize; }
			glm::vec2 GetWindowPosition() const { return m_WindowPosition; }
			bool GetMousePositionInWindow(glm::vec2* mousePosition);

		protected:
			virtual void OnBeginRenderWindow() {}
			virtual void OnRenderWindow(float timestep) = 0;
			virtual void OnEndRenderWindow() {};
			virtual void OnWindowClosedAfterEvents() {}

		private:
			glm::vec2 CalculateWindowSize();
			const std::string GetFullTitle();
			void UpdateSizeAndPosition();

		private:
			static int s_CurrentWindowId;

			std::string m_Title;
			ImGuiWindowFlags m_WindowFlags;
			EventHandler<const ImGuiWindow*> m_WindowClosed;
			bool m_IsOpen = true;
			int m_WindowId;
			glm::vec2 m_WindowSize;
			glm::vec2 m_WindowPosition;
		};
	}
}

