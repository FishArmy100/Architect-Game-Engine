#pragma once
#include "EditorWindow.h"

namespace Editor
{
	class HierarchyWindow : public EditorWindow
	{
	public:
		HierarchyWindow();

	protected:
		void OnRenderWindow(float timestep) override;
	};
}

