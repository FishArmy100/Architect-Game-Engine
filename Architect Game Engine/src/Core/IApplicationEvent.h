#pragma once
#include <string>

namespace Architect
{
	class IApplicationEvent
	{
	public:
		bool IsHandled = false;
		virtual ~IApplicationEvent() {}

		virtual std::string GetDebugString() = 0;
	};
}