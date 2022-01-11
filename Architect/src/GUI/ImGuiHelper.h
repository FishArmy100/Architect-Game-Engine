#pragma once
#include <string>
#include "imgui/imgui.h"
#include "Mathmatics/Color.h"
#include "glm/vec3.hpp"

namespace Architect
{
	namespace UI
	{
		class ImGuiHelper
		{
		public:
			static bool ColorInput(const std::string& label, Color* color);
			static bool Vector3Input(const std::string& label, glm::vec3* vector);
		};
	}
}
