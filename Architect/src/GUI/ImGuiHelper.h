#pragma once
#include <string>
#include "imgui/imgui.h"
#include "Mathmatics/Color.h"

namespace Architect
{
	namespace UI
	{
		class ImGuiHelper
		{
		public:
			static bool ColorInput(const std::string& label, Color* color);
		};
	}
}
