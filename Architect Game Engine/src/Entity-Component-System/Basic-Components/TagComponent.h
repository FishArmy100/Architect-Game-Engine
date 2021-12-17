#pragma once
#include <string>

namespace Architect
{
	struct TagComponent
	{
		std::string Tag;
		TagComponent(std::string tag = "") : Tag(tag) {}
		~TagComponent() {};
		TagComponent(const TagComponent& other) = default;

		operator const std::string& () { return Tag; }
		operator std::string& () { return Tag; }
	};
}