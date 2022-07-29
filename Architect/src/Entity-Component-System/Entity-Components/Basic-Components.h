#pragma once
#include "EntityDataComponent.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "SpriteRendererComponent.h"
#include "HierarchyComponent.h"

// THIS IS PROBLEM
namespace ArchitectTest
{
	struct Test
	{
		Test();
		static volatile Test s_t;
	};
}