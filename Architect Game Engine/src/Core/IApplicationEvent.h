#pragma once
#include <string>

namespace Architect
{
	class IApplicationEvent
	{
	public:
		virtual ~IApplicationEvent() {}
		virtual std::string GetDebugString() = 0;
	};
}