//@	{"targets":[{"name":"integers.hpp","type":"include"}]}

#ifndef TYPE_INTEGERS_HPP
#define TYPE_INTEGERS_HPP

#include "narrow_cast.hpp"
#include <cstdint>
#include <climits>
#include <type_traits>

namespace Type
	{
	template<class T>
	struct IsUnsigned
		{static constexpr bool value = std::is_unsigned<T>::value;};

	template<class T>
	struct IsSigned
		{static constexpr bool value = !IsUnsigned<T>::value;};

	template<class IntegerTypeA, class IntegerTypeB>
	struct SameSignness
		{
		static constexpr bool value=(IsSigned<IntegerTypeA>::value && IsSigned<IntegerTypeB>::value)
			|| (IsUnsigned<IntegerTypeA>::value && IsUnsigned<IntegerTypeB>::value) ;
		};

	template<class From, class To>
	struct LosslessConvertible
		{
		static constexpr bool value=SameSignness<From,To>::value && sizeof(To)>=sizeof(From);
		};


	template<class IntegerType>
	class IntBase
		{
		public:
			template<class U
				,std::enable_if_t<LosslessConvertible<U,IntegerType>::value,int> x=1>
			constexpr IntBase(U value) noexcept:m_value(value)
				{}

			template<class U
				,std::enable_if_t<!LosslessConvertible<U,IntegerType>::value,int> x=1>
			explicit IntBase(U value):m_value(narrow_cast<IntegerType>(value))
				{}

			explicit constexpr operator IntegerType() const noexcept
				{return m_value;}

			static constexpr bool isUnsigned() noexcept
				{return IsUnsigned<IntegerType>::value;}

			static constexpr bool isSigned() noexcept
				{return !isUnsigned();}

		protected:
			IntegerType m_value;
		};

	template<class IntegerType>
	struct IsUnsigned<IntBase<IntegerType>>
		{static constexpr bool value = IntBase<IntegerType>::isUnsigned();};

	enum class IntSize:int
		{
		 Smallest = CHAR_BIT
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
		private:
			template<class Other>
			using EnableForUnsigned = std::enable_if_t<Int::isUnsigned() && std::is_same<Int,Other>::value,Other>;

			template<class Other>
			using EnableForSigned = std::enable_if_t<!Int::isSigned() && std::is_same<Int,Other>::value,Other>;

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
			constexpr Int& operator%=(EnableForUnsigned<Other> a) noexcept
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
			constexpr Int& operator|=(EnableForUnsigned<Other> a) noexcept
				{
				m_value|=a.m_value;
				return *this;
				}

			template<class Other=Int>
			constexpr Int& operator&=(EnableForUnsigned<Other> a) const noexcept
				{
				m_value&=a.m_value;
				return *this;
				}

			template<class Other=Int>
			constexpr Int& operator^=(EnableForUnsigned<Other> a) const noexcept
				{
				m_value^=a.m_value;
				return *this;
				}


			template<class Other=Int>
			constexpr EnableForSigned<Other> operator-() const noexcept
				{return EnableForSigned<Other>(-m_value);}

			template<class Other=Int>
			constexpr EnableForUnsigned<Other> operator~() const noexcept
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
	}

#endif






















