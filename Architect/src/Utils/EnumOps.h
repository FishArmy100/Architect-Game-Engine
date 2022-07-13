#pragma once
#include <type_traits>

template<class T>
struct EnableEnumBitwiseOperators : std::false_type {};

template<typename T>
constexpr bool EnableEnumBitwiseOperatorValue = std::is_enum_v<T> && (bool)EnableEnumBitwiseOperators<T>{};

template<class T>
inline std::enable_if_t<EnableEnumBitwiseOperatorValue<T>, T> operator~ (T a) { return (T)~(std::underlying_type_t<T>)a; }

template<class T>
inline std::enable_if_t<EnableEnumBitwiseOperatorValue<T>, T> operator| (T a, T b) { return (T)((std::underlying_type_t<T>)a | (std::underlying_type_t<T>)b); }

template<class T>
inline std::enable_if_t<EnableEnumBitwiseOperatorValue<T>, T> operator& (T a, T b) { return (T)((std::underlying_type_t<T>)a & (std::underlying_type_t<T>)b); }

template<class T>
inline std::enable_if_t<EnableEnumBitwiseOperatorValue<T>, T> operator^ (T a, T b) { return (T)((std::underlying_type_t<T>)a ^ (std::underlying_type_t<T>)b); }

template<class T>
inline std::enable_if_t<EnableEnumBitwiseOperatorValue<T>, T&> operator|= (T& a, T b) { return (T&)((std::underlying_type_t<T>&)a |= (std::underlying_type_t<T>)b); }

template<class T>
inline std::enable_if_t<EnableEnumBitwiseOperatorValue<T>, T&> operator&= (T& a, T b) { return (T&)((std::underlying_type_t<T>&)a &= (std::underlying_type_t<T>)b); }

template<class T>
inline std::enable_if_t<EnableEnumBitwiseOperatorValue<T>, T&> operator^= (T& a, T b) { return (T&)((std::underlying_type_t<T>&)a ^= (std::underlying_type_t<T>)b); }

#define ARC_ENABLE_ENUM_OPERATIONS(enumTypeName) template<> struct EnableEnumBitwiseOperators<enumTypeName> : std::true_type {};