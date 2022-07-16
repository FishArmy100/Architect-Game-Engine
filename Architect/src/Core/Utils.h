#pragma once
#include <variant>
#include <type_traits>
#include <exception>

namespace Architect
{
	template<typename TVal, typename TError>
	class Result
	{
	static_assert(!std::is_same_v<TVal, TError>, "TVal and TError cannot be the same type");
	public:
		Result(const TVal& val) : m_Variant(val) {}
		Result(const TError& error) : m_Variant(error) {}

		Result(const Result&) = default;
		Result(Result&&) = default;
		Result& operator=(const Result&) = default;
		Result& operator=(Result&&) = default;
		~Result() = default;

		bool IsError() const { return m_Variant.index() == 1; }
		bool IsVal() const { return !IsError(); }

		TVal& Get() { return IsVal() ? std::get<TVal>(m_Variant) : throw std::exception("Cannot access value"); }
		const TVal& Get() const { return IsVal() ? std::get<TVal>(m_Variant) : throw std::exception("Cannot access value"); }

		TError& GetError() { return IsError() ? std::get<TError>(m_Variant) : throw std::exception("Cannot access value"); }
		const TError& GetError() const { return IsError() ? std::get<TError>(m_Variant) : throw std::exception("Cannot access value"); }

		bool operator==(const Result& other) const
		{
			return m_Variant == other.m_Variant;
		}

		bool operator!=(const Result& other) const { return *this == other; }

	private:
		std::variant<TVal, TError> m_Variant;
	};
}