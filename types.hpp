//@	{"targets":[{"name":"types.hpp","type":"include"}]}

#ifndef TYPE_TYPES_HPP
#define TYPE_TYPES_HPP

#include <climits>
#include <cstdint>


namespace Type
	{
	enum IntSize:int
		{
		 Smallest = CHAR_BIT
		,HalfNatural = CHAR_BIT * sizeof(int)/2
		,Natural = CHAR_BIT * sizeof(int)
		,HalfPointer = CHAR_BIT * sizeof(void*)/2
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
	}

#endif
