#pragma once
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"

namespace Architect
{
	class Math
	{
	public:
		static glm::mat4 CalculateTransformMat(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
		static bool DecomposeTransformMatrix(glm::mat4& transform, glm::vec3& postion, glm::vec3& rotation, glm::vec3& scale);
	};
}
