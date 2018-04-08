//@	{"targets":[{"name":"common_types.hpp","type":"include"}]}

#ifndef TYPE_COMMON_TYPES_HPP
#define TYPE_COMMON_TYPES_HPP

#include "integer.hpp"
#include <climits>
#include <cstdint>

namespace Type
	{
	enum class IntSize:int
		{
		 Smallest = CHAR_BIT
		,Short = CHAR_BIT * sizeof(short)
		,Natural = CHAR_BIT * sizeof(int)
 		,Long = CHAR_BIT * sizeof(long)
		,Pointer = CHAR_BIT * sizeof(void*)
		,Largest = CHAR_BIT * sizeof(intmax_t)
		};

	enum class Signedness:int{Signed,Unsigned};

	template<int N,Signedness s>
	struct BitsToIntType;

	template<>
	struct BitsToIntType<8,Signedness::Signed>
		{typedef int8_t type;};

	template<>
	struct BitsToIntType<16,Signedness::Signed>
		{typedef int16_t type;};

	template<>
	struct BitsToIntType<32,Signedness::Signed>
		{typedef int32_t type;};

	template<>
	struct BitsToIntType<64,Signedness::Signed>
		{typedef int64_t type;};

	template<>
	struct BitsToIntType<8,Signedness::Unsigned>
		{typedef uint8_t type;};

	template<>
	struct BitsToIntType<16,Signedness::Unsigned>
		{typedef uint16_t type;};

	template<>
	struct BitsToIntType<32,Signedness::Unsigned>
		{typedef uint32_t type;};

	template<>
	struct BitsToIntType<64,Signedness::Unsigned>
		{typedef uint64_t type;};

	template<int N, Signedness s=Signedness::Signed>
	using SizedInteger = Integer<typename BitsToIntType<N, s>::type>;

	using Tiny = SizedInteger<static_cast<int>(IntSize::Smallest)>;
	using Short = SizedInteger<static_cast<int>(IntSize::Short)>;
	using Int = SizedInteger<static_cast<int>(IntSize::Natural)>;
	using Long = SizedInteger<static_cast<int>(IntSize::Long)>;
	using PtrDiff = SizedInteger<static_cast<int>(IntSize::Pointer)>;
	using Large = SizedInteger<static_cast<int>(IntSize::Largest)>;

	using UTiny = SizedInteger<static_cast<int>(IntSize::Smallest), Signedness::Unsigned>;
	using UShort = SizedInteger<static_cast<int>(IntSize::Short), Signedness::Unsigned>;
	using UInt = SizedInteger<static_cast<int>(IntSize::Natural), Signedness::Unsigned>;
	using ULong = SizedInteger<static_cast<int>(IntSize::Long), Signedness::Unsigned>;
	using Size = SizedInteger<static_cast<int>(IntSize::Pointer), Signedness::Unsigned>;
	using ULarge = SizedInteger<static_cast<int>(IntSize::Largest), Signedness::Unsigned>;

	using Int8 = SizedInteger<8>;
	using Int16 = SizedInteger<16>;
	using Int32 = SizedInteger<32>;
	using Int64 = SizedInteger<64>;

	using UInt8 = SizedInteger<8, Signedness::Unsigned>;
	using UInt16 = SizedInteger<16, Signedness::Unsigned>;
	using UInt32 = SizedInteger<32, Signedness::Unsigned>;
	using UInt64 = SizedInteger<64, Signedness::Unsigned>;
	}

#endif
