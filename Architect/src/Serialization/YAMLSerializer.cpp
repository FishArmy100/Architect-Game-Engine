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

	RefLib::Variant YAMLSerializer::InternalDeserialize(const std::string& data, RefLib::Type expected)
	{
		YAML::Node node = YAML::Load(data);
		if (!node.IsMap())
		{
			Debug::Warning("Invalid yaml document");
			return false;
		}

		if (node["@Version"].as<std::string>() != s_Version)
		{
			Debug::Warning("Yaml document version: " + node["@Version"].as<std::string>() + ", is incompatable with version: " + s_Version);
			return false;
		}

		if (node[expected.GetName()].IsNull())
		{
			Debug::Warning("Serialized object type is incompatable with expected type");
			return false;
		}

		try
		{
			YAML::Node n = node[expected.GetName()];
			return std::move(DeserializeObject(n, expected));
		}
		catch(SerilizationExeption& e)
		{
			Debug::Warning(e.what());
			return false;
		}

		return true;
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

	RefLib::Variant YAMLSerializer::DeserializeObject(YAML::Node& node, RefLib::Type expected)
	{
		if (IsPrimitive(expected))
		{
			return std::move(DeserializePrimitive(node, expected));
		}
		else if (YamlSurrogateSelector::HasSurrogate(expected))
		{
			return std::move(YamlSurrogateSelector::SelectSurrogate(expected).DeserializeFunc(node, expected));
		}
		else if (expected.HasAttribute(RefLib::Type::Get<Serializable>()))
		{
			if (!expected.IsDefaultConstructable())
				throw SerilizationExeption("Type: " + expected.GetName() + ", must have a registared default constructor");

			RefLib::Variant var = expected.Create({});

			for (RefLib::Property prop : expected.GetProperties())
			{
				YAML::Node propNode = node[(std::string)prop.GetName()];
				if (!propNode.IsNull())
				{
					prop.Set(var, DeserializeObject(propNode, prop.GetType()));
				}
			}

			return std::move(var);
		}
		else
		{
			throw SerilizationExeption("Could not deserialize type: " + expected.GetName());
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

		return false;
	}

	RefLib::Variant YAMLSerializer::DeserializePrimitive(YAML::Node& node, RefLib::Type expected)
	{
		return std::move(TryConvert<uint32_t, int32_t, uint64_t, int64_t, float, double, char>(node, expected));
	}

	bool YAMLSerializer::IsPrimitive(RefLib::Type t)
	{
		return IsType<uint32_t, int32_t, uint64_t, int64_t, float, double, char>(t.GetId());
	}
}