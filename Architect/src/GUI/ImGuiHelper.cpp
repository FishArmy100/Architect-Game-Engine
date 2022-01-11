#include "ImGuiHelper.h"
#include <array>

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

		bool ImGuiHelper::Vector3Input(const std::string& label, glm::vec3* vector)
		{
			bool changedVector = false;

			std::array<float, 3> floatArray{ vector->x, vector->y, vector->z };

			changedVector = ImGui::InputFloat3(label.c_str(), floatArray.data());

			vector->x = floatArray[0];
			vector->y = floatArray[1];
			vector->z = floatArray[2];

			return false;
		}
	}
}