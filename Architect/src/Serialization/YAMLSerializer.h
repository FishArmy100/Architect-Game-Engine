#pragma once
#include "RefLib/Instance/Instance.h"
#include "RefLib/Variant/Variant.h"
#include <optional>
#include <string>
#include "yaml-cpp/include/yaml.h"
#include <numeric>
#include "YamlSurrogateSelector.h"
#include "SerializationExeption.h"

namespace Architect
{
	class YAMLSerializer
	{
	public:
		inline static const std::string s_Version = "1.0";
		inline static const std::string s_VersionTag = "@Version";
		inline static const std::string s_BasesTag = "@Bases";

	public:
		YAMLSerializer() = default;
		YAMLSerializer(const YAMLSerializer&) = default;
		~YAMLSerializer() = default;

		template<typename T>
		std::optional<std::string> Serialize(const T& obj) 
		{ 
			return InternalSerialize(obj); 
		}
		
		template<typename T>
		std::optional<T> Deserialize(const std::string& yaml)
		{
			RefLib::Type t = RefLib::Type::Get<T>();
			RefLib::Variant v = InternalDeserialize(yaml, t); 
			return v.TryConvert<T>();
		}

	private:
		std::optional<std::string> InternalSerialize(const RefLib::Variant& obj);
		RefLib::Variant InternalDeserialize(const std::string& data, RefLib::Type expected);

		void SerializeProperty(RefLib::Instance obj, RefLib::Property prop, YAML::Emitter& emitter);
		void SerializeObject(const std::string& name, RefLib::Type objType, const RefLib::Variant& obj, YAML::Emitter& emitter);
		RefLib::Variant DeserializeObject(YAML::Node& node, RefLib::Type expected);
		void SetPropertiesRecursive(RefLib::Variant& obj, RefLib::Type baseType, YAML::Node node);

		bool SerializePrimitive(const RefLib::Variant& v, YAML::Emitter& emitter);
		RefLib::Variant DeserializePrimitive(YAML::Node& node, RefLib::Type expected);
		bool IsPrimitive(RefLib::Type t);

	private:
		using TypeId = RefLib::TypeId;
		template<typename T>
		TypeId GetTypeId() { return RefLib::Type::Get<T>().GetId(); }
		
		template<typename T> 
		bool TryEmit(const RefLib::Variant& v, YAML::Emitter& emitter)
		{
			auto opt = v.TryConvert<T>();
			if (opt.has_value())
			{
				emitter << opt.value();
				return true;
			}
			return false;
		}

		template<typename TFront>
		RefLib::Variant TryConvert(YAML::Node& node, RefLib::Type expected)
		{
			if (RefLib::Type::Get<TFront>().GetId() == expected)
				return std::move(RefLib::Variant(node.as<TFront>()));

			return std::move(RefLib::Variant());
		}

		template<typename TFront, typename TSecond, typename... TTypes>
		RefLib::Variant TryConvert(YAML::Node& node, RefLib::Type expected)
		{
			if (RefLib::Type::Get<TFront>().GetId() == expected)
				return std::move(RefLib::Variant(node.as<TFront>()));

			if constexpr (sizeof...(TTypes) > 0)
				return std::move(TryConvert<TSecond, TTypes...>(node, expected));
			else
				return std::move(TryConvert<TSecond>(node, expected));
		}

		template<typename... TArgs>
		bool IsType(TypeId id) 
		{
			std::array<TypeId, sizeof...(TArgs)> arr = { GetTypeId<TArgs>()... };
			int val = 0;
			for (int i = 0; i < arr.size(); i++) 
				val += (arr[i] == id); 

			return val > 0;
		}

	};
}

