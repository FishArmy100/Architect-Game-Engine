#pragma once
#include "EntityDataComponent.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "SpriteRendererComponent.h"
#include "HierarchyComponent.h"

namespace ArchitectTest
{
	struct Test
	{
		Test();
		static volatile Test s_t;
	};
}