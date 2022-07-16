#pragma once
#include "RefLib/Types/Type.h"
#include "RefLib/Instance/Instance.h"
#include "YamlSerializationSurrogate.h"
#include <map>
#include <memory>
#include "Core.h"

namespace Architect
{
	struct YamlSurrogateWrapper
	{
		std::function<SerializationError(const RefLib::Variant&, YAML::Emitter&)> SerializeFunc;
		std::function<Result<RefLib::Variant, SerializationError>(YAML::Node&, RefLib::Type)> DeserializeFunc;
	};

	class YamlSurrogateSelector 
	{
	public:
		template<typename T>
		static void AddSurrogate()
		{
			YamlSurrogateWrapper wrapper;
			wrapper.SerializeFunc = [](const RefLib::Variant& var, YAML::Emitter& e)
			{
				RefLib::Type t = RefLib::Type::Get<T>();
				RefLib::Type vt = var.GetType();
				if (vt.GetId() == t.GetId() || t.IsDerivedFrom(vt))
					return YamlSerializationSurrogate<T>().OnSerialize(*(T*)var.GetRawData(), e);

				return SerializationError("Could not convert " + vt.GetName() + ", to " + t.GetName());
			};

			wrapper.DeserializeFunc = [](YAML::Node& node, RefLib::Type expected) -> Result<RefLib::Variant, SerializationError>
			{
				RefLib::Type t = RefLib::Type::Get<T>();

				if (expected.GetId() == t.GetId())
				{
					auto r = YamlSerializationSurrogate<T>().OnDeserialize(node, expected);
					if (r.IsError()) return r.GetError();

					return std::move(RefLib::Variant(r.Get()));
				}

				return SerializationError("Could not convert " + expected.GetName() + ", to " + t.GetName());
			};

			m_Surrogates[RefLib::Type::Get<T>().GetId()] = wrapper;
		}
		static bool HasSurrogate(RefLib::TypeId id);
		static YamlSurrogateWrapper SelectSurrogate(RefLib::TypeId id);

	private:
		static inline std::map<RefLib::TypeId, YamlSurrogateWrapper> m_Surrogates = {};
	};

}
