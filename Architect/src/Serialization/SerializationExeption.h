#pragma once
#include <exception>
#include <string>

namespace Architect
{
	struct SerilizationExeption : std::exception 
	{
		SerilizationExeption(const std::string& message) :std::exception(message.c_str()) {}
		SerilizationExeption(const char* message) : std::exception(message) {}
		SerilizationExeption(const SerilizationExeption&) = default;
		virtual ~SerilizationExeption() = default;
	};
}