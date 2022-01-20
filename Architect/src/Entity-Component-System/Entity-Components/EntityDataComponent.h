#pragma once
#include <string>
#include "Mathmatics/UUID.h"

namespace Architect
{
	class EntityDataComponent
	{
	public:
		EntityDataComponent(const std::string& name, bool isActive = true, uint64_t uuid = UUID::NewUUID());

		std::string Name;
		bool IsActive;
		uint64_t GetUUID() const { return m_Uuid; }

	private:
		uint64_t m_Uuid;
	};
}