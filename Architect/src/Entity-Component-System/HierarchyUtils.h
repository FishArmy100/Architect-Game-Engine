#pragma once
#include "Scene.h"
#include "glm/mat4x4.hpp"

namespace Architect
{
	class HierarchyUtils
	{
	public:
		static void SetParent(Scene* scene, EntityID entity, EntityID parent);
		static void ClearParent(Scene* scene, EntityID entity); 
		static bool ContainsDecedent(Scene* scene, EntityID entity, EntityID decendent);
		static glm::mat4 LocalToWorld(Scene* scene, EntityID parent, glm::mat4 localTransform);
		static glm::mat4 WorldToLocal(Scene* scene, EntityID parent, glm::mat4 worldTransform);
		static std::vector<EntityID> GetDecendents(Scene* scene, EntityID entity);
	};
}

