#include "ImGuiHelper.h"

namespace Architect
{
	namespace UI
	{
		bool ImGuiHelper::ColorInput(const std::string& label, Color* color)
		{
			float* colorArray = color->GetFloatArray().data();
			bool valueChanged = ImGui::ColorPicker4(label.c_str(), colorArray);
			color->SetValues(colorArray[0], colorArray[1], colorArray[2], colorArray[3]);
			return valueChanged;
		}
	}
}