//@	{"targets":[{"name":"integers.hpp","type":"include"}]}

#ifndef TYPE_INTEGERS_HPP
#define TYPE_INTEGERS_HPP

#include "int_base.hpp"
#include "types.hpp"
#include <climits>

namespace Type
	{
	template<int N=IntSize::Natural,Signedness s=Signedness::Signed>
	class Integer:public IntBase<typename BitsToIntType<N,s>::type>
		{
		//TODO: Add max
		//TODO: Add min
		//TODO: Add zero
		//TODO: Add unity
		//TODO: Add addInv (only for signed)

		private:
			template<class Other>
			using EnableForUnsigned = std::enable_if<Integer::isUnsigned() && std::is_same<Integer,Other>::value,Other>;

			template<class Other>
			using EnableForSigned = std::enable_if<Integer::isSigned() && std::is_same<Integer,Other>::value,Other>;

		public:
			using IntBase<typename BitsToIntType<N,s>::type>::IntBase;
			using IntBase<typename BitsToIntType<N,s>::type>::isUnsigned;
			using IntBase<typename BitsToIntType<N,s>::type>::isSigned;
			using IntBase<typename BitsToIntType<N,s>::type>::m_value;

			constexpr Integer& operator+=(Integer a) noexcept
				{
				m_value+=a.m_value;
				return *this;
				}

			constexpr Integer& operator-=(Integer a) noexcept
				{
				m_value-=a.m_value;
				return *this;
				}

			constexpr Integer& operator*=(Integer a) noexcept
				{
				m_value*=a.m_value;
				return *this;
				}

			constexpr Integer& operator/=(Integer a) noexcept
				{
				m_value/=a.m_value;
				return *this;
				}

			template<class Other=Integer>
			constexpr Integer& operator%=(typename EnableForUnsigned<Other>::type a) noexcept
				{
				m_value%=a.m_value;
				return *this;
				}

			constexpr Integer& operator<<=(Integer a) noexcept
				{
				m_value<<=a.m_value;
				return *this;
				}

			constexpr Integer& operator>>=(Integer a) noexcept
				{
				m_value>>=a.m_value;
				return *this;
				}

			template<class Other=Integer>
			constexpr Integer& operator|=(typename EnableForUnsigned<Other>::type a) noexcept
				{
				m_value|=a.m_value;
				return *this;
				}

			template<class Other=Integer>
			constexpr Integer& operator&=(typename EnableForUnsigned<Other>::type a) const noexcept
				{
				m_value&=a.m_value;
				return *this;
				}

			template<class Other=Integer>
			constexpr Integer& operator^=(typename EnableForUnsigned<Other>::type a) const noexcept
				{
				m_value^=a.m_value;
				return *this;
				}


			template<class Other=Integer>
			constexpr typename EnableForSigned<Other>::type operator-() const noexcept
				{return EnableForSigned<Other>(-m_value);}

			template<class Other=Integer>
			constexpr typename EnableForUnsigned<Other>::type operator~() const noexcept
				{return EnableForUnsigned<Other>(~m_value);}



			constexpr bool operator<(Integer b) const noexcept
				{return m_value < b.m_value;}

			constexpr bool operator>(Integer b) const noexcept
				{return b < *this;}

			constexpr bool operator==(Integer b) const noexcept
				{return m_value == b.m_value;}

			constexpr bool operator!=(Integer b) const noexcept
				{return !(*this == b);}

			constexpr bool operator<=(Integer b) const noexcept
				{return !(*this > b);}

			constexpr bool operator>=(Integer b) const noexcept
				{return !(*this < b);}

			constexpr Integer& operator++() noexcept
				{
				++m_value;
				return *this;
				}

			constexpr Integer operator++(int) const noexcept
				{
				auto ret = *this;
				++m_value;
				return ret;
				}
		};


	template<int N,Signedness s>
	inline constexpr Integer<N,s> operator+(Integer<N,s> a, Integer<N,s> b) noexcept
		{return a+=b;}

	template<int N,Signedness s>
	inline constexpr Integer<N,s> operator-(Integer<N,s> a, Integer<N,s> b) noexcept
		{return a-=b;}

	template<int N,Signedness s>
	inline constexpr Integer<N,s> operator*(Integer<N,s> a, Integer<N,s> b) noexcept
		{return a*=b;}

	template<int N,Signedness s>
	inline constexpr Integer<N,s> operator/(Integer<N,s> a, Integer<N,s> b) noexcept
		{return a/=b;}

	template<int N,Signedness s>
	inline constexpr Integer<N,s> operator%(Integer<N,s> a, Integer<N,s> b) noexcept
		{return a%=b;}

	template<int N,Signedness s>
	inline constexpr Integer<N,s> operator<<(Integer<N,s> a, Integer<N,s> b) noexcept
		{return a<<=b;}

	template<int N,Signedness s>
	inline constexpr Integer<N,s> operator>>(Integer<N,s> a, Integer<N,s> b) noexcept
		{return a>>=b;}

	template<int N,Signedness s>
	inline constexpr Integer<N,s> operator|(Integer<N,s> a, Integer<N,s> b) noexcept
		{return a|=b;}

	template<int N,Signedness s>
	inline constexpr Integer<N,s> operator&(Integer<N,s> a, Integer<N,s> b) noexcept
		{return a&=b;}

	template<int N,Signedness s>
	inline constexpr Integer<N,s> operator^=(Integer<N,s> a, Integer<N,s> b) noexcept
		{return a^=b;}

	//TODO: add aliases for common types
	}

#endif






















