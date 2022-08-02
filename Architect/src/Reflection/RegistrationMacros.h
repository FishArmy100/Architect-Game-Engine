#pragma once
#include "RefLib/Registration/TypeRegistrationFactory.h"
#include "RefLib/Registration/HelperRegistrationMacros.h"

#define ARC_FRIEND template<typename T> friend struct RefLib::TypeRegistrationFactory;

#define ARC_REFLECT(name)\
template<>														\
struct RefLib::TypeRegistrationFactory<name> : std::true_type	\
{																\
	void operator()();											\
};

namespace ArchitectInternal
{
	template<typename T>
	class RegisterTypeAuto;

	template<typename T>
	struct Cookie;

	template<typename T>
	static void* init_cookie_keeper;
}

#define ARC_REFLECT_AUTO_HELPER(name)										\
	namespace ArchitectInternal												\
	{																		\
		template<>															\
		struct RegisterTypeAuto<name>										\
		{																	\
			RegisterTypeAuto();												\
			static RegisterTypeAuto s_Auto;									\
		};																	\
		template<>															\
		struct Cookie<name>													\
		{																	\
			static void* GetData();											\
		};																	\
		template<>															\
		static void* init_cookie_keeper<name> = Cookie<name>::GetData();	\
	}

#define ARC_REFLECT_AUTO(name)		\
	ARC_REFLECT_AUTO_HELPER(name)	\
	ARC_REFLECT(name)


#define ARC_BEGIN_CLASS(name)\
	namespace RefLib\
	{\
		void TypeRegistrationFactory<name>::operator()()\
		{\
			REFLIB_BEGIN_CLASS(name)

#define ARC_BEGIN_CLASS_AUTO_HELPER(name)								\
	namespace ArchitectInternal											\
	{																	\
		RegisterTypeAuto<name>::RegisterTypeAuto()						\
		{																\
			RefLib::Type::Get<name>();									\
		}																\
		RegisterTypeAuto<name> RegisterTypeAuto<name>::s_Auto = {};		\
		void* Cookie<name>::GetData() { return nullptr; }				\
	}

#define ARC_BEGIN_CLASS_AUTO(name)		\
	ARC_BEGIN_CLASS_AUTO_HELPER(name)	\
	ARC_BEGIN_CLASS(name)

#define ARC_BEGIN_METADATA() REFLIB_END_CLASS();

#define ARC_END_METADATA_CLASS() }}

#define ARC_END_CLASS() REFLIB_END_CLASS() }}


