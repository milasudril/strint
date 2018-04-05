//@	{"targets":[{"name":"integers.hpp","type":"include"}]}

#ifndef TYPE_INTEGERS_HPP
#define TYPE_INTEGERS_HPP

#include "int_base.hpp"

#include "narrow_cast.hpp"
#include <cstdint>
#include <climits>

namespace Type
	{
	enum class IntSize:int
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

	template<int N=IntSize::Natural,Signedness s=Signedness::Signed>
	class Int:public IntBase<typename BitsToIntType<N,s>::type>
		{
		//TODO: Rename this class to Integer
		//TODO: Add max
		//TODO: Add min
		//TODO: Add zero
		//TODO: Add unity
		//TODO: Add addInv (only for signed)

		private:
			typedef Int<N, s> Self;

			template<class Other>
			using EnableForUnsigned = std::enable_if<Int::isUnsigned() && std::is_same<Int,Other>::value,Other>;

			template<class Other>
			using EnableForSigned = std::enable_if<Int::isSigned() && std::is_same<Int,Other>::value,Other>;

		public:
			using IntBase<typename BitsToIntType<N,s>::type>::IntBase;
			using IntBase<typename BitsToIntType<N,s>::type>::isUnsigned;
			using IntBase<typename BitsToIntType<N,s>::type>::isSigned;
			using IntBase<typename BitsToIntType<N,s>::type>::m_value;

			constexpr Int& operator+=(Int a) noexcept
				{
				m_value+=a.m_value;
				return *this;
				}

			constexpr Int& operator-=(Int a) noexcept
				{
				m_value-=a.m_value;
				return *this;
				}

			constexpr Int& operator*=(Int a) noexcept
				{
				m_value*=a.m_value;
				return *this;
				}

			constexpr Int& operator/=(Int a) noexcept
				{
				m_value/=a.m_value;
				return *this;
				}

			template<class Other=Int>
			constexpr Int& operator%=(typename EnableForUnsigned<Other>::type a) noexcept
				{
				m_value%=a.m_value;
				return *this;
				}

			constexpr Int& operator<<=(Int a) noexcept
				{
				m_value<<=a.m_value;
				return *this;
				}

			constexpr Int& operator>>=(Int a) noexcept
				{
				m_value>>=a.m_value;
				return *this;
				}

			template<class Other=Int>
			constexpr Int& operator|=(typename EnableForUnsigned<Other>::type a) noexcept
				{
				m_value|=a.m_value;
				return *this;
				}

			template<class Other=Int>
			constexpr Int& operator&=(typename EnableForUnsigned<Other>::type a) const noexcept
				{
				m_value&=a.m_value;
				return *this;
				}

			template<class Other=Int>
			constexpr Int& operator^=(typename EnableForUnsigned<Other>::type a) const noexcept
				{
				m_value^=a.m_value;
				return *this;
				}


			template<class Other=Int>
			constexpr typename EnableForSigned<Other>::type operator-() const noexcept
				{return EnableForSigned<Other>(-m_value);}

			template<class Other=Int>
			constexpr typename EnableForUnsigned<Other>::type operator~() const noexcept
				{return EnableForUnsigned<Other>(~m_value);}



			constexpr bool operator<(Int b) const noexcept
				{return m_value < b.m_value;}

			constexpr bool operator>(Int b) const noexcept
				{return b < *this;}

			constexpr bool operator==(Int b) const noexcept
				{return m_value == b.m_value;}

			constexpr bool operator!=(Int b) const noexcept
				{return !(*this == b);}

			constexpr bool operator<=(Int b) const noexcept
				{return !(*this > b);}

			constexpr bool operator>=(Int b) const noexcept
				{return !(*this < b);}

			constexpr Int& operator++() noexcept
				{
				++m_value;
				return *this;
				}

			constexpr Int operator++(int) const noexcept
				{
				auto ret = *this;
				++m_value;
				return ret;
				}
		};


	template<int N,Signedness s>
	inline constexpr Int<N,s> operator+(Int<N,s> a, Int<N,s> b) noexcept
		{return a+=b;}

	template<int N,Signedness s>
	inline constexpr Int<N,s> operator-(Int<N,s> a, Int<N,s> b) noexcept
		{return a-=b;}

	template<int N,Signedness s>
	inline constexpr Int<N,s> operator*(Int<N,s> a, Int<N,s> b) noexcept
		{return a*=b;}

	template<int N,Signedness s>
	inline constexpr Int<N,s> operator/(Int<N,s> a, Int<N,s> b) noexcept
		{return a/=b;}

	template<int N,Signedness s>
	inline constexpr Int<N,s> operator%(Int<N,s> a, Int<N,s> b) noexcept
		{return a%=b;}

	template<int N,Signedness s>
	inline constexpr Int<N,s> operator<<(Int<N,s> a, Int<N,s> b) noexcept
		{return a<<=b;}

	template<int N,Signedness s>
	inline constexpr Int<N,s> operator>>(Int<N,s> a, Int<N,s> b) noexcept
		{return a>>=b;}

	template<int N,Signedness s>
	inline constexpr Int<N,s> operator|(Int<N,s> a, Int<N,s> b) noexcept
		{return a|=b;}

	template<int N,Signedness s>
	inline constexpr Int<N,s> operator&(Int<N,s> a, Int<N,s> b) noexcept
		{return a&=b;}

	template<int N,Signedness s>
	inline constexpr Int<N,s> operator^=(Int<N,s> a, Int<N,s> b) noexcept
		{return a^=b;}

	//TODO: add aliases for common types
	}

#endif






















