//@	{"targets":[{"name":"common_types.test","type":"application","autorun":1}]}

#include "common_types.hpp"
#include "stic/stic.hpp"

STIC_TESTCASE("Sizes correct")
	{
	STIC_ASSERT(sizeof(Strint::Tiny) == sizeof(char));
	STIC_ASSERT(sizeof(Strint::Short) == sizeof(short));
	STIC_ASSERT(sizeof(Strint::Int) == sizeof(int));
	STIC_ASSERT(sizeof(Strint::Long) == sizeof(long));
	STIC_ASSERT(sizeof(Strint::Large) == sizeof(intmax_t));
	STIC_ASSERT(sizeof(Strint::PtrDiff) == sizeof(void*));

	STIC_ASSERT(sizeof(Strint::UTiny) == sizeof(unsigned char));
	STIC_ASSERT(sizeof(Strint::UShort) == sizeof(unsigned short));
	STIC_ASSERT(sizeof(Strint::UInt) == sizeof(unsigned int));
	STIC_ASSERT(sizeof(Strint::ULong) == sizeof(unsigned long));
	STIC_ASSERT(sizeof(Strint::ULarge) == sizeof(uintmax_t));
	STIC_ASSERT(sizeof(Strint::Size) == sizeof(void*));

	STIC_ASSERT(sizeof(Strint::Int8) == sizeof(int8_t));
	STIC_ASSERT(sizeof(Strint::Int16) == sizeof(int16_t));
	STIC_ASSERT(sizeof(Strint::Int32) == sizeof(int32_t));
	STIC_ASSERT(sizeof(Strint::Int64) == sizeof(int64_t));

	STIC_ASSERT(sizeof(Strint::UInt8) == sizeof(uint8_t));
	STIC_ASSERT(sizeof(Strint::UInt16) == sizeof(uint16_t));
	STIC_ASSERT(sizeof(Strint::UInt32) == sizeof(uint32_t));
	STIC_ASSERT(sizeof(Strint::UInt64) == sizeof(uint64_t));
	}

STIC_TESTCASE("Signedness correct")
	{
	STIC_ASSERT(Strint::Tiny::isSigned());
	STIC_ASSERT(Strint::Short::isSigned());
	STIC_ASSERT(Strint::Int::isSigned());
	STIC_ASSERT(Strint::Long::isSigned());
	STIC_ASSERT(Strint::Large::isSigned());
	STIC_ASSERT(Strint::PtrDiff::isSigned());

	STIC_ASSERT(Strint::UTiny::isUnsigned());
	STIC_ASSERT(Strint::UShort::isUnsigned());
	STIC_ASSERT(Strint::UInt::isUnsigned());
	STIC_ASSERT(Strint::ULong::isUnsigned());
	STIC_ASSERT(Strint::ULarge::isUnsigned());
	STIC_ASSERT(Strint::Size::isUnsigned());

	STIC_ASSERT(Strint::Int8::isSigned());
	STIC_ASSERT(Strint::Int16::isSigned());
	STIC_ASSERT(Strint::Int32::isSigned());
	STIC_ASSERT(Strint::Int64::isSigned());

	STIC_ASSERT(Strint::UInt8::isUnsigned());
	STIC_ASSERT(Strint::UInt16::isUnsigned());
	STIC_ASSERT(Strint::UInt32::isUnsigned());
	STIC_ASSERT(Strint::UInt64::isUnsigned());
	}
