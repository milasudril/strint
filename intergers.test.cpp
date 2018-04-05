//@	{"targets":[{"name":"integers.test","type":"application","autorun":1}]}

#include "integers.hpp"
#include "stic/stic.hpp"

#include <cstdio>


STIC_TESTCASE("Range test")
	{
	typedef Type::Integer<16, Type::Signedness::Unsigned> UInt16;
	STIC_ASSERT_THROW(UInt16 x(-1););
	STIC_ASSERT_THROW(UInt16 x(std::numeric_limits<uint16_t>::max() + 1););
	STIC_ASSERT_NOTHROW(UInt16 x(0););
	STIC_ASSERT_NOTHROW(UInt16 x(std::numeric_limits<uint16_t>::max()););

	typedef Type::Integer<16> Int16;
	STIC_ASSERT_THROW(Int16 x(std::numeric_limits<int16_t>::min() - 1););
	STIC_ASSERT_THROW(Int16 x(std::numeric_limits<int16_t>::max() + 1););
	STIC_ASSERT_NOTHROW(Int16 x(std::numeric_limits<int16_t>::min()););
	STIC_ASSERT_NOTHROW(Int16 x(std::numeric_limits<int16_t>::max()););
	}

STIC_TESTCASE("Subtraction inverse of addition")
	{
	typedef Type::Integer<8, Type::Signedness::Unsigned> UInt8;
	constexpr UInt8 val_init(0);
	constexpr UInt8 val_max(std::numeric_limits<uint8_t>::max());
	for(auto val = val_init; val<val_max; ++val)
		{
		for(auto k=val; k<val_max - val; ++k)
			{
			auto sum = val + k;
			STIC_ASSERT(sum - k == val);
			}
		}
	}

STIC_TESTCASE("Can use standard size")
	{
	Type::Integer<> val(0);
	STIC_ASSERT(sizeof(val)==sizeof(int));
	}

STIC_TESTCASE("Type conversion")
	{
	Type::Integer<16> a(123);
	Type::Integer<32> b(a);
	Type::Integer<16> c(b);
	}
