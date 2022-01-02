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

		operator std::string& () { return Tag; }
	};
}