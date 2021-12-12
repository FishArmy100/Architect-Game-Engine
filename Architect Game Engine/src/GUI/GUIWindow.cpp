#include "GUIWindow.h"
#include "imgui/imgui.h"
#include <iterator>

namespace Architect
{
	namespace UI
	{
		GUIWindow::GUIWindow(const std::string& title) : m_Title(title)
		{
			
		}

		GUIWindow::~GUIWindow()
		{

		}

		void GUIWindow::RenderWindow()
		{
			ImGui::Begin(m_Title.c_str());
			OnRenderWindow();
			ImGui::End();
		}

		void GUIWindow::Text(const std::string& text)
		{
			ImGui::Text(text.c_str());
		}

		void GUIWindow::CheckBox(const std::string& label, bool* b)
		{
			ImGui::Checkbox(label.c_str(), b);
		}

		bool GUIWindow::Button(const std::string& label)
		{
			return ImGui::Button(label.c_str());
		}

		void GUIWindow::FloatSlider(const std::string& label, float* f, float max, float min)
		{
			ImGui::SliderFloat(label.c_str(), f, min, max);
		}

		bool GUIWindow::FloatInput(const std::string& label, float* f)
		{
			return ImGui::InputFloat(label.c_str(), f);
		}

		bool GUIWindow::IntInput(const std::string& label, int* i)
		{
			return ImGui::InputInt(label.c_str(), i);
		}

		bool GUIWindow::ColorInput(const std::string& label, Color* color)
		{
			float* colorArray = color->GetFloatArray().data();
			bool valueChanged = ImGui::ColorPicker4(label.c_str(), colorArray);
			color->SetValues(colorArray[0], colorArray[1], colorArray[2], colorArray[3]);
			return valueChanged;
		}
	}
}