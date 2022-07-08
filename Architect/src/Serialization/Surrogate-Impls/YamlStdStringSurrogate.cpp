#include "YamlStdStringSurrogate.h"

namespace Architect
{
	SerializationError YamlSerializationSurrogate<std::string>::OnSerialize(const std::string& str, YAML::Emitter& emitter)
	{
		emitter << str;
		return SerializationError::GetNoError();
	}
}