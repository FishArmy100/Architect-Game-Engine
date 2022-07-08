#pragma once
#include "RefLib/Types/Type.h"
#include "YamlSerializationSurrogate.h"
#include <map>
#include <memory>
#include "Core.h"

namespace Architect
{
	struct YamlSurrogateWrapper
	{
		std::function<SerializationError(const RefLib::Variant&, YAML::Emitter&)> SerializeFunc;
	};

	class YamlSurrogateSelector 
	{
	public:
		YamlSurrogateSelector() = default;
		YamlSurrogateSelector(const YamlSurrogateSelector&) = delete;
		~YamlSurrogateSelector() = default;

		template<typename T>
		void AddSurrogate() 
		{
			YamlSurrogateWrapper wrapper;
			wrapper.SerializeFunc = [](const RefLib::Variant& var, YAML::Emitter& e)
			{
				RefLib::Type t = RefLib::Type::Get<T>();
				RefLib::Type vt = var.GetType(); 
				if (vt.GetId() == t.GetId())
					return YamlSerializationSurrogate<T>().OnSerialize(var.TryConvert<T>().value(), e); 

				return SerializationError("Could not convert " + vt.GetName() + ", to " + t.GetName());  
			};

			m_Surrogates[RefLib::Type::Get<T>().GetId()] = wrapper;
		}

		bool HasSurrogate(RefLib::TypeId id);
		YamlSurrogateWrapper SelectSurrogate(RefLib::TypeId id);

	private:
		std::map<RefLib::TypeId, YamlSurrogateWrapper> m_Surrogates;
	};

}
