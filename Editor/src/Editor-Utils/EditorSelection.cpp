#include "EditorSelection.h"

namespace Editor
{
	std::shared_ptr<EditorSelection> EditorSelection::s_CurrentSelection = nullptr;
	EventHandler<void> EditorSelection::s_SelectionChanged;

	EditorSelection::EditorSelection(Entity e) : m_Entity(e)
	{
	}

	void EditorSelection::SetCurrentSelection(std::shared_ptr<EditorSelection> newSelection)
	{
		s_CurrentSelection = newSelection;
		s_SelectionChanged.Invoke();
	}

	bool EditorSelection::HasSelection(EditorSelection selection)
	{
		if (s_CurrentSelection == nullptr)
			return false;

		return *s_CurrentSelection == selection;
	}

	bool EditorSelection::operator==(const EditorSelection& lhs)
	{
		return this->GetEntity() == lhs.GetEntity();
	}
}