#pragma once
#include "Core/Events.h"

namespace Editor
{
	enum class EditorMode
	{
		Edit,
		Play
	};

	class EditorSettings
	{
	public:
		EditorSettings(EditorMode mode = EditorMode::Edit, bool isPaused = false);
		~EditorSettings() = default;

		static void SetSettings(EditorSettings settings) { s_CurrentSettings = settings; }
		static EditorSettings& GetSettings() { return s_CurrentSettings; }

	public:
		EditorMode Mode;
		bool IsPaused;

	private:
		static EditorSettings s_CurrentSettings;
	};
}

