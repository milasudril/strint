//@	{"targets":[{"name":"common_types.test","type":"application","autorun":1}]}

#include "common_types.hpp"
#include "stic/stic.hpp"

STIC_TESTCASE("Sizes correct")
	{
	STIC_ASSERT(sizeof(Type::Tiny) == sizeof(char));
	STIC_ASSERT(sizeof(Type::Short) == sizeof(short));
	STIC_ASSERT(sizeof(Type::Int) == sizeof(int));
	STIC_ASSERT(sizeof(Type::Long) == sizeof(long));
	STIC_ASSERT(sizeof(Type::Large) == sizeof(intmax_t));
	STIC_ASSERT(sizeof(Type::PtrDiff) == sizeof(void*));

	STIC_ASSERT(sizeof(Type::UTiny) == sizeof(unsigned char));
	STIC_ASSERT(sizeof(Type::UShort) == sizeof(unsigned short));
	STIC_ASSERT(sizeof(Type::UInt) == sizeof(unsigned int));
	STIC_ASSERT(sizeof(Type::ULong) == sizeof(unsigned long));
	STIC_ASSERT(sizeof(Type::ULarge) == sizeof(uintmax_t));
	STIC_ASSERT(sizeof(Type::Size) == sizeof(void*));

	STIC_ASSERT(sizeof(Type::Int8) == sizeof(int8_t));
	STIC_ASSERT(sizeof(Type::Int16) == sizeof(int16_t));
	STIC_ASSERT(sizeof(Type::Int32) == sizeof(int32_t));
	STIC_ASSERT(sizeof(Type::Int64) == sizeof(int64_t));

	STIC_ASSERT(sizeof(Type::UInt8) == sizeof(uint8_t));
	STIC_ASSERT(sizeof(Type::UInt16) == sizeof(uint16_t));
	STIC_ASSERT(sizeof(Type::UInt32) == sizeof(uint32_t));
	STIC_ASSERT(sizeof(Type::UInt64) == sizeof(uint64_t));
	}

STIC_TESTCASE("Signedness correct")
	{
	STIC_ASSERT(Type::Tiny::isSigned());
	STIC_ASSERT(Type::Short::isSigned());
	STIC_ASSERT(Type::Int::isSigned());
	STIC_ASSERT(Type::Long::isSigned());
	STIC_ASSERT(Type::Large::isSigned());
	STIC_ASSERT(Type::PtrDiff::isSigned());

	STIC_ASSERT(Type::UTiny::isUnsigned());
	STIC_ASSERT(Type::UShort::isUnsigned());
	STIC_ASSERT(Type::UInt::isUnsigned());
	STIC_ASSERT(Type::ULong::isUnsigned());
	STIC_ASSERT(Type::ULarge::isUnsigned());
	STIC_ASSERT(Type::Size::isUnsigned());

	STIC_ASSERT(Type::Int8::isSigned());
	STIC_ASSERT(Type::Int16::isSigned());
	STIC_ASSERT(Type::Int32::isSigned());
	STIC_ASSERT(Type::Int64::isSigned());

	STIC_ASSERT(Type::UInt8::isUnsigned());
	STIC_ASSERT(Type::UInt16::isUnsigned());
	STIC_ASSERT(Type::UInt32::isUnsigned());
	STIC_ASSERT(Type::UInt64::isUnsigned());
	}
