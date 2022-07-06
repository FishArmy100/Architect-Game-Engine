#include "YAMLSerializer.h"
#include "RefLib/Property/Property.h"
#include "RefLib/Registration/BasicSTDRegistration.h"
#include "Serializeable.h"

namespace Architect
{
	std::optional<std::string> YAMLSerializer::InternalSerialize(const RefLib::Variant& obj)
	{
		YAML::Emitter emitter;

	}

	RefLib::Variant YAMLSerializer::InternalDeserialize(const std::string& data)
	{
		return RefLib::Variant();
	}

	void YAMLSerializer::SerializeProperty(RefLib::Instance parent, RefLib::Property prop, YAML::Emitter& emitter)
	{
		RefLib::Type propType = prop.GetType();

		if (IsPrimitive(propType))
		{
			emitter << YAML::Key << (std::string)prop.GetName();
			emitter << YAML::Value;
			SerializePrimitive(prop.Get(parent), emitter); 
		}
		else if(propType.HasAttribute(RefLib::Type::Get<Serializable>()))
		{
			emitter << YAML::Key << (std::string)prop.GetName();
			emitter << YAML::Value << YAML::BeginMap;
			RefLib::Variant propVal = prop.Get(parent);

			for (const auto& subProp : propType.GetProperties())
			{
				SerializeProperty(propVal, subProp, emitter);
			}

			emitter << YAML::EndMap; 
		}
	}

	bool YAMLSerializer::SerializePrimitive(const RefLib::Variant& v, YAML::Emitter& emitter)
	{
		TypeId id = v.GetType().GetId();
		if (TryEmit<uint32_t>	(v, emitter)) { return true; }
		if (TryEmit<int32_t>	(v, emitter)) { return true; }
		if (TryEmit<uint64_t>	(v, emitter)) { return true; }
		if (TryEmit<int64_t>	(v, emitter)) { return true; }
		if (TryEmit<float>		(v, emitter)) { return true; }
		if (TryEmit<double>		(v, emitter)) { return true; }
		if (TryEmit<char>		(v, emitter)) { return true; }
		if (TryEmit<wchar_t>	(v, emitter)) { return true; }

		return false;
	}

	bool YAMLSerializer::IsPrimitive(RefLib::Type t)
	{
		return IsType<uint32_t, int32_t, uint64_t, int64_t, float, double, char, wchar_t>(t.GetId());
	}
}