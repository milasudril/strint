//@	{"targets":[{"name":"integers.test","type":"application","autorun":1}]}

#include "integers.hpp"
#include "stic/stic.hpp"


STIC_TESTCASE("Range test")
	{
	typedef Type::Integer<uint16_t> UInt16;
	STIC_ASSERT_THROW(UInt16 x(-1););
	STIC_ASSERT_THROW(UInt16 x(std::numeric_limits<uint16_t>::max() + 1););
	STIC_ASSERT_NOTHROW(UInt16 x(0););
	STIC_ASSERT_NOTHROW(UInt16 x(std::numeric_limits<uint16_t>::max()););

	typedef Type::Integer<int16_t> Int16;
	STIC_ASSERT_THROW(Int16 x(std::numeric_limits<int16_t>::min() - 1););
	STIC_ASSERT_THROW(Int16 x(std::numeric_limits<int16_t>::max() + 1););
	STIC_ASSERT_NOTHROW(Int16 x(std::numeric_limits<int16_t>::min()););
	STIC_ASSERT_NOTHROW(Int16 x(std::numeric_limits<int16_t>::max()););
	}

STIC_TESTCASE("Can use standard size")
	{
	Type::Integer<> val(0);
	STIC_ASSERT(sizeof(val)==sizeof(int));
	}

STIC_TESTCASE("Invert bits")
	{
	typedef Type::Integer<uint8_t> UInt8;

	UInt8 x(128);
	UInt8 y(0);
	STIC_ASSERT_NOTHROW(y = ~x;);
	STIC_ASSERT(y == UInt8(0x7f));
	}

STIC_TESTCASE("Negate")
	{
	typedef Type::Integer<int8_t> Int8;

	Int8 x(127);
	Int8 y(0);
	STIC_ASSERT_NOTHROW(y = -x;);
	STIC_ASSERT(y == Int8(-127));
	}

STIC_TESTCASE("Subtraction inverse of addition")
	{
	typedef Type::Integer<uint8_t> UInt8;
	for(auto val = UInt8::min(); val < UInt8::max(); ++val)
		{
		for(auto k=val; k < UInt8::max() - val; ++k)
			{
			auto sum = val + k;
			STIC_ASSERT(sum - k == val);
			}
		}
	}

STIC_TESTCASE("Type conversion")
	{
	int x_1 = 123;
	int x_2 = 456;

	Type::Integer<short> a(x_1);
	Type::Integer<int> b(a);
	STIC_ASSERT(Type::Integer<int>(x_1) == b);
	Type::Integer<short> c(x_2);

	b = c;
	STIC_ASSERT(Type::Integer<int>(x_2) == b);

	Type::Integer<short> d(b);
	STIC_ASSERT(Type::Integer<short>(x_2) == d);
	STIC_ASSERT(b == d);
	STIC_ASSERT(d == b);

	Type::Integer<short> e(1234);

	STIC_ASSERT_THROW( Type::Integer<char> f{e};);
	}

STIC_TESTCASE("Type names")
	{
	printf("%s\n", Type::Integer<short>::type());
	}
