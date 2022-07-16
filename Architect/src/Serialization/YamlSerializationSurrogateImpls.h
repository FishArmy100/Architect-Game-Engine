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

		Result<std::string, SerializationError> OnDeserialize(YAML::Node& node, RefLib::Type expected)
		{
			return node.as<std::string>();
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

		Result<std::vector<T>, SerializationError> OnDeserialize(YAML::Node& node, RefLib::Type expected)
		{
			if constexpr (std::is_default_constructible_v<T>)
			{
				YAMLSerializer s{};
				std::vector<T> vec;
				for (YAML::Node cn : node)
				{
					vec.push_back(s.Deserialize<T>(cn.as<std::string>()).value());
				}

				return std::move(vec);
			}
			else
			{
				static_assert("Type T must be default constructable");
			}
		}
	};
}