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
}

#define ARC_REFLECT_AUTO(name)					\
	namespace ArchitectInternal					\
	{											\
		template<>								\
		struct RegisterTypeAuto<name>			\
		{										\
			RegisterTypeAuto();					\
			static RegisterTypeAuto s_Auto;		\
		};										\
	}											\
	ARC_REFLECT(name)


#define ARC_BEGIN_CLASS(name)\
	namespace RefLib\
	{\
		void TypeRegistrationFactory<name>::operator()()\
		{\
			REFLIB_BEGIN_CLASS(name)


#define ARC_BEGIN_CLASS_AUTO(name)\
	ArchitectInternal::RegisterTypeAuto<name>::RegisterTypeAuto() {RefLib::Type::Get<name>();}\
	ArchitectInternal::RegisterTypeAuto<name> ArchitectInternal::RegisterTypeAuto<name>::s_Auto = {};\
	ARC_BEGIN_CLASS(name)

#define ARC_BEGIN_METADATA() REFLIB_END_CLASS();

#define ARC_END_METADATA_CLASS() }}

#define ARC_END_CLASS() REFLIB_END_CLASS() }}


