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
		void DrawEntity(Entity e);

	private:
		std::unordered_set<uint32_t> m_DrawnEntities;

	};
}

