// RefLib
#include "RefLib/Registration/HelperRegistrationMacros.h"
#include "RefLib/Registration/BasicSTDRegistration.h"
#include "RefLib/Registration/TypeRegistrationFactory.h"

// Other:
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "Serialization/Serializeable.h"

REFLIB_REGISTRATION
{
	// glm::vec3
	REFLIB_BEGIN_CLASS(glm::vec3)
		REFLIB_ATTRIBUTE(Architect::Serializable{})
		REFLIB_CTOR()
		REFLIB_CTOR(const glm::vec3&)
		REFLIB_CTOR(float, float, float)
		REFLIB_PROP_BASIC(x)
		REFLIB_PROP_BASIC(y)
		REFLIB_PROP_BASIC(z)
	REFLIB_END_CLASS()

	// glm::vec2
	REFLIB_BEGIN_CLASS(glm::vec2)
		REFLIB_ATTRIBUTE(Architect::Serializable{})
		REFLIB_CTOR()
		REFLIB_CTOR(const glm::vec2&)
		REFLIB_CTOR(float, float)
		REFLIB_PROP_BASIC(x)
		REFLIB_PROP_BASIC(y)
	REFLIB_END_CLASS()
}