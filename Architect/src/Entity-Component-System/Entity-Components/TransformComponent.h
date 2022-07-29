#pragma once
#include "glm/ext.hpp"
#include <vector>
#include "entt/entt.hpp"
#include "Reflection/RegistrationMacros.h"

namespace Architect
{
	enum class WorldSpace
	{
		Global,
		Local
	};

	struct TransformComponent
	{
		TransformComponent(glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1));
		~TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;

		glm::vec3 Position;
		glm::vec3 Rotation;
		glm::vec3 Scale;

		glm::mat4 LocalToWorld;
		glm::mat4 LocalToParent;

		void Translate(glm::vec3 direction);
		void Rotate(glm::vec3 rotation);

		void Dilate(float scale);
		void Dilate(glm::vec3 scale);
	};
}

namespace ArchitectInternal
{
	template<>
	struct RegisterTypeAuto<Architect::TransformComponent>
	{
		RegisterTypeAuto();
		static RegisterTypeAuto s_Auto;
	};
}

ARC_REFLECT(Architect::TransformComponent)

//ARC_REFLECT_AUTO(Architect::TransformComponent)



