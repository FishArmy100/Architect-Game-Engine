#pragma once
#include "RefLib/Types/Type.h"
#include "RefLib/Variant/Variant.h"
#include "yaml-cpp/include/yaml.h"
#include "SerializationError.h"
#include "Core/Utils.h"
#include <variant>

namespace Architect
{
	template<typename T>
	struct YamlSerializationSurrogate
	{
		SerializationError OnSerialize(const T& obj, YAML::Emitter& emitter)
		{
			static_assert(false, "SerializationError OnSerialize(const T& obj, YAML::Emitter& emitter) must be implemented");
		}

		Result<T, SerializationError> OnDeserialize(YAML::Node& node, RefLib::Type expected)
		{
			static_assert(false, "Result<T, SerializationError> OnDeserialize((YAML::Node& node, RefLib::Type expected) must be implemented");
		}
	};
}

