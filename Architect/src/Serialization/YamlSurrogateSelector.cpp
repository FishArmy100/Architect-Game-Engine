#include "YamlSurrogateSelector.h"

namespace Architect
{
	bool YamlSurrogateSelector::HasSurrogate(RefLib::TypeId id)
	{
		return m_Surrogates.find(id) != m_Surrogates.end();
	}

	YamlSurrogateWrapper YamlSurrogateSelector::SelectSurrogate(RefLib::TypeId id)
	{
		return m_Surrogates.at(id);
	}
}
