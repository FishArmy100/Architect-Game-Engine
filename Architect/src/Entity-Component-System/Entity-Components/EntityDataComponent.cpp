#include "EntityDataComponent.h"


namespace Architect
{
	EntityDataComponent::EntityDataComponent(const std::string& name, bool isActive, uint64_t uuid) :
		Name(name), IsActive(isActive), m_Uuid(uuid)
	{
	}
}