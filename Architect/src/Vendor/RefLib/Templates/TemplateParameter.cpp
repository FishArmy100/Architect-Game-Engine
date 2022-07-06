#include "TemplateParameter.h"
#include "RefLib/Types/Type.h"

namespace RefLib
{
	TemplateParameter::TemplateParameter(TypeId type, const std::string& name, int index) :
		ParamType(type), Name(name), Index(index)
	{
	}

	Type TemplateParameter::GetType()
	{
		return Type::Get(ParamType).value();
	}
}