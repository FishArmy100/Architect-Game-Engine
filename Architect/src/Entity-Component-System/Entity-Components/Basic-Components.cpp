#include "Basic-Components.h"
#include "RefLib/Registration/HelperRegistrationMacros.h"
#include "Serialization/Serializeable.h"
#include "Entity-Component-System/ComponentRegistry.h"
#include "RefLib/Registration/RegistrationFriend.h"

namespace ArchitectInternal
{
	RegisterTypeAuto<Architect::TransformComponent>::RegisterTypeAuto()
	{
		RefLib::Type::Get<Architect::TransformComponent>();
	}

	RegisterTypeAuto<Architect::TransformComponent> RegisterTypeAuto<Architect::TransformComponent>::s_Auto = {};
}

namespace ArchitectTest
{
	Test::Test() { std::cout << "Called!" << "\n"; }
	Test volatile Test::s_t = {};
}

ARC_BEGIN_CLASS(Architect::TransformComponent)
	REFLIB_CTOR(const Architect::TransformComponent&)
	REFLIB_CTOR()
	REFLIB_CTOR(glm::vec3, glm::vec3, glm::vec3)
	REFLIB_PROP_BASIC(Position)
	REFLIB_PROP_BASIC(Rotation)
	REFLIB_PROP_BASIC(Scale)
	REFLIB_ATTRIBUTE(Architect::Serializable{})
ARC_BEGIN_METADATA()
	ARC_REGISTER_COMPONENT(Architect::TransformComponent)
ARC_END_METADATA_CLASS()

ARC_BEGIN_CLASS(Architect::EntityDataComponent)
	REFLIB_CTOR()
	REFLIB_CTOR(const Architect::EntityDataComponent&)
	REFLIB_CTOR(const std::string&, bool, uint64_t)
	REFLIB_PROP_BASIC(Name)
	REFLIB_PROP_BASIC(IsActive)
	REFLIB_PROP_ACCESS(m_Uuid, RefLib::AccessLevel::Private)
ARC_BEGIN_METADATA()
	ARC_REGISTER_COMPONENT(Architect::TransformComponent)
ARC_END_METADATA_CLASS()

ARC_BEGIN_CLASS(Architect::HierarchyComponent)
	REFLIB_CTOR()
	REFLIB_CTOR(const Architect::HierarchyComponent&)
	REFLIB_PROP_BASIC(Parent)
	REFLIB_PROP_BASIC(Children)
ARC_BEGIN_METADATA()
	ARC_REGISTER_COMPONENT(Architect::HierarchyComponent)
ARC_END_METADATA_CLASS()

ARC_BEGIN_CLASS(Architect::CameraComponent)
	REFLIB_CTOR(Architect::Camera)
	REFLIB_PROP_BASIC(Camera)
	REFLIB_ATTRIBUTE(Architect::Serializable([]() -> RefLib::Variant { return Architect::CameraComponent(Architect::Camera(0, 0)); }))
ARC_BEGIN_METADATA()
	ARC_REGISTER_COMPONENT(Architect::CameraComponent)
ARC_END_METADATA_CLASS()
