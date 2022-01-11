#pragma once
#include "Core/Events.h"
#include "Entity-Component-System/Entity.h"
#include <memory>

namespace Editor
{
	using namespace Architect;

	class EditorSelection
	{
	public:
		EditorSelection(Entity e);

		static void SetCurrentSelection(std::shared_ptr<EditorSelection> newSelection);
		static std::shared_ptr<EditorSelection> GetCurrentSelection() { return s_CurrentSelection; }
		static bool HasSelection() { return s_CurrentSelection != nullptr; }
		static bool HasSelection(EditorSelection selection);

		static EventHandler<void>& GetSelectionChanged() { return s_SelectionChanged; }

		const Entity& GetEntity() const { return m_Entity; }

		bool operator==(const EditorSelection& lhs);
		bool operator!=(const EditorSelection& lhs) { return !(*this == lhs); }

	private:
		static std::shared_ptr<EditorSelection> s_CurrentSelection;
		static EventHandler<void> s_SelectionChanged;

		Entity m_Entity;
	};
}

