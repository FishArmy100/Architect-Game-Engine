#pragma once
#include <string>

namespace Architect
{
	class SerializationError
	{
	public:
		static inline SerializationError GetNoError() { return SerializationError(); }

	public:
		SerializationError() : m_IsError(false), m_ErrorMessage() {}
		SerializationError(const std::string& message) : m_IsError(true), m_ErrorMessage(message) {}
		SerializationError(const SerializationError&) = default;
		~SerializationError() = default;

		const std::string& Message() { return m_ErrorMessage; }
		bool HasError() { return m_IsError; }

	private:
		bool m_IsError;
		std::string m_ErrorMessage;
	};
}