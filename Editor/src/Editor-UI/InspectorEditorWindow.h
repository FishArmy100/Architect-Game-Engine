#pragma once
#include "EditorWindow.h"

namespace Editor
{
	using namespace Architect;

	class InspectorEditorWindow : public EditorWindow
	{
	public: 
		InspectorEditorWindow();

	protected:
		void OnRenderWindow() override;
	};
}

