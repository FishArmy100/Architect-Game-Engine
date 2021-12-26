#pragma once
#include <string>
#include "../Mathmatics/Color.h"
#include "imgui/imgui.h"

namespace Architect
{
	namespace UI
	{
		class GUIWindow
		{
		private:
			std::string m_Title;

		public:
			GUIWindow(const std::string& title = "Window");
			~GUIWindow();

			void RenderWindow();
			const std::string GetName() const { return m_Title; }

		protected:
			virtual void OnRenderWindow() = 0;

			void Text(const std::string& text);
			void CheckBox(const std::string& label, bool* b);
			bool Button(const std::string& label);
			void FloatSlider(const std::string& label, float* f, float max = 1.0f, float min = 0.0f);
			bool FloatInput(const std::string& label, float* f);
			bool IntInput(const std::string& label, int* i);
			bool ColorInput(const std::string& label, Color* color);
		};
	}
}

