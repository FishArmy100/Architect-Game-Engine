#pragma once
#include "RefLib/Types/Type.h"
#include "RefLib/Variant/Variant.h"
#include "yaml-cpp/include/yaml.h"
#include "SerializationError.h"

namespace Architect
{
	template<typename T>
	struct YamlSerializationSurrogate
	{
		SerializationError OnSerialize(const T& obj, YAML::Emitter& emitter)
		{
			static_assert("OnSerialize(const T& obj, YAML::Emitter& emitter) must be implemented");
		}
	};
}

