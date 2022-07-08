#pragma once
#include "Serialization/YamlSerializationSurrogate.h"

namespace Architect
{
	template<>
	struct YamlSerializationSurrogate<std::string>
	{
		SerializationError OnSerialize(const std::string& str, YAML::Emitter& emitter);
	};
}

