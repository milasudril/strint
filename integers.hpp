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
		private:
			template<class Other>
			using EnableForUnsigned = std::enable_if<Integer::isUnsigned() && std::is_same<Integer,Other>::value,Other>;

			template<class Other>
			using EnableForSigned = std::enable_if<Integer::isSigned() && std::is_same<Integer,Other>::value,Other>;

		public:
			typedef IntBase<typename BitsToIntType<N,s>::type> Base;

			using Base::IntBase;
			using Base::isUnsigned;
			using Base::isSigned;
			using Base::m_value;



			static constexpr Integer max() noexcept
				{return std::numeric_limits<typename Base::Rep>::max();}

			static constexpr Integer min() noexcept
				{return std::numeric_limits<typename Base::Rep>::min();}

			static constexpr Integer zero() noexcept
				{return Integer(static_cast<typename Base::Rep>(0));}

			static constexpr Integer unity() noexcept
				{return Integer(static_cast<typename Base::Rep>(1));}

			template<class Other=Integer>
			static constexpr typename EnableForSigned<Other>::type additiveInverse() noexcept
				{return typename EnableForSigned<Other>::type(static_cast<typename Base::Rep>(-1));}



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
				{return typename EnableForSigned<Other>::type(static_cast<typename Base::Rep>(-m_value));}

			template<class Other=Integer>
			constexpr typename EnableForUnsigned<Other>::type operator~() const noexcept
				{return typename EnableForUnsigned<Other>::type(static_cast<typename Base::Rep>(~m_value));}



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
				++ret.m_value;
				return ret;
				}

			constexpr Integer& operator--() noexcept
				{
				--m_value;
				return *this;
				}

			constexpr Integer operator--(int) const noexcept
				{
				auto ret = *this;
				--ret.m_value;
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



	template<class Type,int N,Signedness s>
	inline constexpr std::enable_if_t<!IsLosslessConvertible<Integer<N,s>,Type>::value,bool>
	operator==(Type a, Integer<N,s> b) noexcept
		{return b==a;}

	template<class Type,int N,Signedness s>
	inline constexpr std::enable_if_t<!IsLosslessConvertible<Integer<N,s>,Type>::value,bool>
	operator!=(Type a, Integer<N,s> b) noexcept
		{return !(a==b);}

	template<class Type,int N,Signedness s>
	inline constexpr std::enable_if_t<!IsLosslessConvertible<Integer<N,s>,Type>::value,bool>
	operator<(Type a, Integer<N,s> b) noexcept
		{return b>a;}

	template<class Type,int N,Signedness s>
	inline constexpr std::enable_if_t<!IsLosslessConvertible<Integer<N,s>,Type>::value,bool>
	operator>(Type a, Integer<N,s> b) noexcept
		{return b<a;}

	template<class Type,int N,Signedness s>
	inline constexpr std::enable_if_t<!IsLosslessConvertible<Integer<N,s>,Type>::value,bool>
	operator<=(Type a, Integer<N,s> b) noexcept
		{return !(a>b);}

	template<class Type,int N,Signedness s>
	inline constexpr std::enable_if_t<!IsLosslessConvertible<Integer<N,s>,Type>::value,bool>
	operator>=(Type a, Integer<N,s> b) noexcept
		{return !(a<b);}

	//TODO: add aliases for common types
	}

#endif






















