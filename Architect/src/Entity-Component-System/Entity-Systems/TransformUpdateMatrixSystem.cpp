#include "TransformUpdateMatrixSystem.h"
#include "Entity-Component-System/Entity-Components/TransformComponent.h"
#include "Entity-Component-System/Entity-Components/HierarchyComponent.h"
#include "Entity-Component-System/Entity.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "glm/ext/matrix_transform.hpp"

namespace Architect
{
	TransformUpdateMatrixSystem::TransformUpdateMatrixSystem() : UpdateEntitySystem("Transform Update Matrix System")
	{
	}

	glm::mat4 GetWorldPositionFromLocalPosition(Scene* scene, EntityID entity)
	{
		HierarchyComponent& hierarchy = scene->GetComponentFromEntity<HierarchyComponent>(entity);
		TransformComponent& transform = scene->GetComponentFromEntity<TransformComponent>(entity);

		if (hierarchy.Parent == NullEntity)
			return transform.LocalToParent;
		else
			return GetWorldPositionFromLocalPosition(scene, hierarchy.Parent) * transform.LocalToParent;
	}

	void TransformUpdateMatrixSystem::OnUpdate(std::shared_ptr<Scene> scene, float timestep)
	{
		std::function<void(TransformComponent&)> updateLocalPosition = [](TransformComponent& transform)
		{
			transform.LocalToParent =
				glm::translate(glm::mat4(1.0f), transform.Position)
				* glm::toMat4(glm::quat(glm::radians(transform.Rotation)))
				* glm::scale(glm::mat4(1.0f), transform.Scale);
		};

		std::function<void(Entity& e, TransformComponent&, HierarchyComponent&)> updateGlobalPosition = [](Entity& e, TransformComponent& transform, HierarchyComponent& hierarchy)
		{
			if (hierarchy.Parent == NullEntity)
			{
				transform.LocalToWorld = transform.LocalToParent;
			}
			else
			{
				transform.LocalToWorld = GetWorldPositionFromLocalPosition(e.GetScene(), e);
			}
		};

		scene->GetEntitiesWithComponent<TransformComponent>(updateLocalPosition);
		scene->GetEntitiesWithComponent<TransformComponent, HierarchyComponent>(updateGlobalPosition);
	}
}
