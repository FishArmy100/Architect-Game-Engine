#include "YAMLSerializer.h"
#include "RefLib/Property/Property.h"
#include "RefLib/Registration/BasicSTDRegistration.h"
#include "Serializeable.h"
#include "Debug-System/Debug.h"

namespace Architect
{
	std::optional<std::string> YAMLSerializer::InternalSerialize(const RefLib::Variant& obj)
	{
		YAML::Emitter emitter;
		emitter << YAML::BeginMap;
		emitter << YAML::Key << s_VersionTag;
		emitter << YAML::Value << s_Version;

		try { SerializeObject(obj.GetType().GetName(), obj.GetType(), obj, emitter); }
		catch (SerilizationExeption& e)
		{
			Debug::Warning(e.what());
			return {};
		}

		emitter << YAML::EndMap;

		return std::string(emitter.c_str());
	}

	RefLib::Variant YAMLSerializer::InternalDeserialize(const std::string& data)
	{
		return RefLib::Variant();
	}

	void YAMLSerializer::SerializeProperty(RefLib::Instance parent, RefLib::Property prop, YAML::Emitter& emitter)
	{
		SerializeObject((std::string)prop.GetName(), prop.GetType(), prop.Get(parent), emitter);
	}

	void YAMLSerializer::SerializeObject(const std::string& name, RefLib::Type objType, const RefLib::Variant& obj, YAML::Emitter& emitter)
	{
		if (IsPrimitive(objType))
		{
			emitter << YAML::Key << name; 
			emitter << YAML::Value;
			SerializePrimitive(obj, emitter);
		}
		else if (YamlSurrogateSelector::HasSurrogate(objType))
		{
			emitter << YAML::Key << name;
			emitter << YAML::Value;
			SerializationError error = YamlSurrogateSelector::SelectSurrogate(objType).SerializeFunc(obj, emitter);

			if (error.HasError())
				throw SerilizationExeption(error.Message());
		}
		else if (objType.HasAttribute(RefLib::Type::Get<Serializable>()))
		{
			emitter << YAML::Key << name;
			emitter << YAML::Value << YAML::BeginMap;
			RefLib::Variant objVal = obj;

			for (const auto& subProp : objType.GetProperties())
			{
				SerializeProperty(objVal, subProp, emitter);
			}

			if (objType.GetBaseTypes().size() > 0)
			{
				emitter << YAML::Key << s_BasesTag;
				emitter << YAML::Value << YAML::BeginMap;

				for (const auto& base : objType.GetBaseTypes())
				{
					SerializeObject(base.Data.GetName(), base.Data, obj, emitter);
				}

				emitter << YAML::EndMap;
			}

			emitter << YAML::EndMap;
		}
		else
		{
			throw SerilizationExeption("Type: " + obj.GetType().GetName() + ", Cannot be serialized");
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