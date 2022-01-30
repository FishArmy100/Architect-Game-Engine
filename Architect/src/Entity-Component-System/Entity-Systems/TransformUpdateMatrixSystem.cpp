#include "TransformUpdateMatrixSystem.h"
#include "Entity-Component-System/Entity-Components/TransformComponent.h"
#include "Entity-Component-System/Entity-Components/HierarchyComponent.h"
#include "Entity-Component-System/Entity.h"
#include "Mathmatics/Math.h"
#include "Entity-Component-System/HierarchyUtils.h"



namespace Architect
{
	TransformUpdateMatrixSystem::TransformUpdateMatrixSystem() : UpdateEntitySystem("Transform Update Matrix System")
	{
	}

	void TransformUpdateMatrixSystem::OnUpdate(std::shared_ptr<Scene> scene, float timestep)
	{
		scene->GetEntitesWithComponent<TransformComponent>([](Entity e, TransformComponent& transform) 
		{
			transform.LocalToParent = Math::CalculateTransformMat(transform.Position, transform.Rotation, transform.Scale);
		});

		scene->GetEntitesWithComponent<TransformComponent, HierarchyComponent>([](Entity e, TransformComponent& transform, HierarchyComponent& hierarchy)
		{
			if (hierarchy.Parent == NullEntity)
				transform.LocalToWorld = transform.LocalToParent;
			else
				transform.LocalToWorld = HierarchyUtils::LocalToWorld(e.GetScene(), hierarchy.Parent, transform.LocalToParent);
		});
	}
}
