#pragma once
#include "glm/vec2.hpp"
#include "Vector2.h"

namespace Architect
{
	namespace Math
	{
		Vector2 GLMV2ToVec2(const glm::vec2& glmVec)
		{
			return Vector2(glmVec.x, glmVec.y);
		}

		glm::vec2 Vec2ToGLMVec2(const Vector2& vec)
		{
			return glm::vec2(vec.X, vec.Y);
		}
	}
}
