#pragma once
#include "YamlSerializationSurrogate.h"
#include "YAMLSerializer.h"

namespace Architect
{
	template<>
	struct YamlSerializationSurrogate<std::string> 
	{
		SerializationError OnSerialize(const std::string& str, YAML::Emitter& emitter)
		{
			emitter << str;
			return SerializationError::GetNoError(); 
		}
	};

	template<typename T>
	struct YamlSerializationSurrogate<std::vector<T>>
	{
		SerializationError OnSerialize(const std::vector<T>& vec, YAML::Emitter& emitter)
		{
			emitter << YAML::BeginSeq;

			for (const auto& val : vec)
			{
				YAMLSerializer s{};
				std::optional<std::string> result = s.Serialize(val);

				if (!result) { return SerializationError("Could vector of type: " + RefLib::Type::Get<std::vector<T>>().GetName()); }

				emitter << result.value();
			}
			
			emitter << YAML::EndSeq;

			return SerializationError::GetNoError();
		}
	};
}