#pragma once
#include "EditorWindow.h"
#include <unordered_set>
#include "Entity-Component-System/Entity.h"

namespace Editor
{
	class HierarchyWindow : public EditorWindow
	{
	public:
		HierarchyWindow();

	protected:
		void OnRenderWindow() override;

	private:
		void DrawEntityPopupMenu();
		void ShowEntityPopupMenu();
		void DrawEntity(Entity e);
		void HandleDragDrop(Entity e);

		enum class HierarchyEditType { Ordering, Parenting };

	private:
		std::unordered_set<uint32_t> m_DrawnEntities;
		HierarchyEditType m_EditType = HierarchyEditType::Parenting;
	};
}

