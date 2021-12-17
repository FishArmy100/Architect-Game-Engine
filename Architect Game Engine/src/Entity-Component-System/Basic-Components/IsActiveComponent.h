#pragma once

namespace Architect
{
	struct IsActiveComponent
	{
		bool IsActive;
		IsActiveComponent(bool isActive) : IsActive(isActive) {}
		~IsActiveComponent() {};
		IsActiveComponent(const IsActiveComponent& other) = default;

		operator const bool() { return IsActive; }
		operator bool() { return IsActive; }
	};
}