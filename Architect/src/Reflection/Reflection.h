#pragma once
#include "rttr/registration.h"
#include "rttr/registration_friend.h"

namespace Architect
{
	namespace Reflection
	{
		using TypeInfo = rttr::type;

		using TypeId = rttr::type::type_id;

		using FunctionInfo = rttr::method;
		using ConstructorInfo = rttr::constructor;
		using ParameterInfo = rttr::parameter_info;
		using PropertyInfo = rttr::property;

		using EnumInfo = rttr::enumeration;

		using Variant = rttr::variant;
		using Instance = rttr::instance;
		using Argument = rttr::argument;

		using Metadata = rttr::detail::metadata;

		template<typename T>
		using ArrayRange = rttr::array_range<T>;

		template<typename T> 
		std::optional<T> IndexArrayRange(ArrayRange<T>&& range, int index)
		{
			int i = 0;
			for (T data : range)
			{
				if (i == index)
					return data;
				i++;
			}

			return {};
		}

		struct AccessLevel
		{
			static constexpr rttr::detail::public_access Public = rttr::registration::public_access;
			static constexpr rttr::detail::protected_access Protected = rttr::registration::protected_access;
			static constexpr rttr::detail::private_access Private = rttr::registration::private_access;
		};

		struct TypeUtils
		{
			template<typename T>
			static TypeInfo GetType() { return rttr::type::get<T>(); }

			template<typename T>
			static TypeId GetTypeId() { return GetType<T>().get_id(); }
		};

		struct AttributeUtils
		{
			template<typename T>
			static Metadata CreateAttributeMetadata(T&& attribute) { return Metadata(TypeUtils::GetType<T>(), attribute); }

			template<typename T>
			static std::optional<T> GetAttribute(TypeInfo info)
			{
				Variant v = info.get_metadata(TypeUtils::GetType<T>());
				if (v.is_valid() && v.can_convert<T>())
					return v.get_value<T>();

				return {};
			}

			template<typename T>
			static std::optional<T> GetAttribute(FunctionInfo info)
			{
				Variant v = info.get_metadata(TypeUtils::GetType<T>());
				if (v.is_valid() && v.can_convert<T>())
					return v.get_value<T>();

				return {};
			}

			template<typename T>
			static std::optional<T> GetAttribute(PropertyInfo info)
			{
				Variant v = info.get_metadata(TypeUtils::GetType<T>());
				if (v.is_valid() && v.can_convert<T>())
					return v.get_value<T>();

				return {};
			}

			template<typename T>
			static std::optional<T> GetAttribute(ConstructorInfo info)
			{
				Variant v = info.get_metadata(TypeUtils::GetType<T>());
				if (v.is_valid() && v.can_convert<T>())
					return v.get_value<T>();

				return {};
			}
		};
	}
}

#define ARC_USE_REFLECTION using namespace Architect::Reflection

// Class begin registration
#define ARC_BEGIN_REGISTER_CLASS(classType)						\
namespace Register__Class__##classType {						\
using ClassType = classType;									\
static const char* className = #classType;						\
static void Auto__Register__Type__Func();						\
struct Auto__Register__Type__Struct								\
{																\
	Auto__Register__Type__Struct()								\
	{															\
		Auto__Register__Type__Func();							\
	}															\
};																\
																\
static const Auto__Register__Type__Struct register__instance__;	\
static void Auto__Register__Type__Func() {						\
rttr::registration::class_<ClassType>(className)

// Class end registration
#define ARC_END_REGISTER_CLASS ;}}

// Property registration
#define ARC_REGISTER_PROPERTY(accessLevel, propertyName)					\
	.property(#propertyName, &ClassType::propertyName, accessLevel)

// Function registration
#define ARC_REGISTER_FUNCTION(accessLevel, functionSignature, functionName)	\
	.method(#functionName, rttr::select_overload<functionSignature>(&ClassType::functionName), accessLevel)

// Constructor registration
#define ARC_REGISTER_CONSTRUCTOR(accessLevel, ...)							\
	.constructor<__VA_ARGS__>(accessLevel)

// creating attribute data
#define ARC_ATTRIB(attribute) Architect::Reflection::AttributeUtils::CreateAttributeMetadata(attribute)

// creating metadata
#define ARC_METADATA(key, value) rttr::metadata(key, value);

#define ARC_PARAM_NAMES(...) rttr::parameter_names(__VA_ARGS__)

// Class utils/freind registration
#define ARC_ENABLE_CLASS_REFLECTION(...) RTTR_REGISTRATION_FRIEND RTTR_ENABLE(__VA_ARGS__);

#define ARC_GLOBAL_ENUM_VAL(name) rttr::value(#name, EnumType::name)

#define ARC_REGISTER_GLOBAL_ENUM_CLASS(enumName, ...)				\
namespace Register__Enum__##enumName {								\
using EnumType = enumName;											\
static void Auto__Register__Type__Func();							\
struct Auto__Register__Type__Struct									\
{																	\
	Auto__Register__Type__Struct()									\
	{																\
		Auto__Register__Type__Func();								\
	}																\
};																	\
																	\
static const Auto__Register__Type__Struct register__instance__;		\
static void Auto__Register__Type__Func() {							\
	rttr::registration::enumeration<enumName>(#enumName)			\
	(__VA_ARGS__);													\
}}

