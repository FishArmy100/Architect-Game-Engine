#include "EditorSettings.h"


namespace Editor
{
	EditorSettings EditorSettings::s_CurrentSettings = EditorSettings();

	EditorSettings::EditorSettings(EditorMode mode, bool isPaused) :
		Mode(mode), IsPaused(isPaused)
	{

	}
}


