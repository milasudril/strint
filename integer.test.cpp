//@	{"targets":[{"name":"integer.test","type":"application","autorun":1}]}

#include "integer.hpp"
#include "stic/stic.hpp"
#include <cstring>

STIC_TESTCASE("Range tests")
	{
	typedef Type::Integer<uint16_t> UInt16;
	STIC_ASSERT_THROW(UInt16 x(-1););
	STIC_ASSERT_THROW(UInt16 x(std::numeric_limits<uint16_t>::max() + 1););
	STIC_ASSERT_NOTHROW(UInt16 x(0););
	STIC_ASSERT_NOTHROW(UInt16 x(std::numeric_limits<uint16_t>::max()););
	STIC_ASSERT(UInt16::min() == std::numeric_limits<uint16_t>::min());
	STIC_ASSERT(UInt16::max() == std::numeric_limits<uint16_t>::max());

	typedef Type::Integer<int16_t> Int16;
	STIC_ASSERT_THROW(Int16 x(std::numeric_limits<int16_t>::min() - 1););
	STIC_ASSERT_THROW(Int16 x(std::numeric_limits<int16_t>::max() + 1););
	STIC_ASSERT_NOTHROW(Int16 x(std::numeric_limits<int16_t>::min()););
	STIC_ASSERT_NOTHROW(Int16 x(std::numeric_limits<int16_t>::max()););
	STIC_ASSERT(Int16::min() == std::numeric_limits<int16_t>::min());
	STIC_ASSERT(Int16::max() == std::numeric_limits<int16_t>::max());
	}

STIC_TESTCASE("Can use standard size")
	{
	Type::Integer<> val(0);
	STIC_ASSERT(sizeof(val)==sizeof(int));
	STIC_ASSERT(val.isSigned());
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
	STIC_ASSERT(Type::Integer<int8_t>::typeId() == Type::TypeId::Int8);
	STIC_ASSERT(Type::Integer<int16_t>::typeId() == Type::TypeId::Int16);
	STIC_ASSERT(Type::Integer<int32_t>::typeId() == Type::TypeId::Int32);
	STIC_ASSERT(Type::Integer<int64_t>::typeId() == Type::TypeId::Int64);

	STIC_ASSERT(strcmp(Type::Integer<int8_t>::typeName(),"i8") == 0);
	STIC_ASSERT(strcmp(Type::Integer<int16_t>::typeName(),"i16") == 0);
	STIC_ASSERT(strcmp(Type::Integer<int32_t>::typeName(),"i32") == 0);
	STIC_ASSERT(strcmp(Type::Integer<int64_t>::typeName(),"i64") == 0);

	STIC_ASSERT(Type::Integer<uint8_t>::typeId() == Type::TypeId::UInt8);
	STIC_ASSERT(Type::Integer<uint16_t>::typeId() == Type::TypeId::UInt16);
	STIC_ASSERT(Type::Integer<uint32_t>::typeId() == Type::TypeId::UInt32);
	STIC_ASSERT(Type::Integer<uint64_t>::typeId() == Type::TypeId::UInt64);

	STIC_ASSERT(strcmp(Type::Integer<uint8_t>::typeName(),"u8") == 0);
	STIC_ASSERT(strcmp(Type::Integer<uint16_t>::typeName(),"u16") == 0);
	STIC_ASSERT(strcmp(Type::Integer<uint32_t>::typeName(),"u32") == 0);
	STIC_ASSERT(strcmp(Type::Integer<uint64_t>::typeName(),"u64") == 0);
	}
