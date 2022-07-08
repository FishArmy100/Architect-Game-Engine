#pragma once
#include "RefLib/Instance/Instance.h"
#include "RefLib/Variant/Variant.h"
#include <optional>
#include <string>
#include "yaml-cpp/include/yaml.h"
#include <numeric>
#include "YamlSurrogateSelector.h"

namespace Architect
{
	class YAMLSerializer
	{
	public:
		inline static const std::string s_Version = "1.0";

	public:
		YAMLSerializer(std::unique_ptr<YamlSurrogateSelector>&& selector);
		YAMLSerializer(const YAMLSerializer&) = default;
		~YAMLSerializer() = default;

		template<typename T>
		std::optional<std::string> Serialize(const T& obj) { return InternalSerialize(obj); }
		
		template<typename T>
		std::optional<T> Deserialize(const std::string& yaml) 
		{
			RefLib::Variant var = InternalDeserialize(yaml); 
			if (var.IsValid())
				return var.TryConvert<T>();
			return {};
		}

	private:
		std::unique_ptr<YamlSurrogateSelector> m_Selector;

	private:
		std::optional<std::string> InternalSerialize(const RefLib::Variant& obj); 
		RefLib::Variant InternalDeserialize(const std::string& data);
		void SerializeProperty(RefLib::Instance obj, RefLib::Property prop, YAML::Emitter& emitter);
		bool SerializePrimitive(const RefLib::Variant& v, YAML::Emitter& emitter);
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

