//@	{"targets":[{"name":"integer.hpp","type":"include"}]}

#ifndef STRINT_INTEGER_HPP
#define STRINT_INTEGER_HPP

#include "narrow_cast.hpp"
#include "type_names.hpp"

#include <climits>

namespace Strint
	{
	template<class To, class From>
	inline constexpr
	std::enable_if_t<IsLosslessConvertible<From,To>::value, To>
	cast_helper(From val) noexcept
		{return static_cast<To>(val);}

	template<class IntegerType=int>
	class Integer
		{
		public:
			static constexpr bool isUnsigned() noexcept
				{return IsUnsigned<IntegerType>::value;}

			static constexpr bool isSigned() noexcept
				{return !isUnsigned();}

			static constexpr const char* typeName() noexcept
				{return TypeInfo<IntegerType>::name;}

			static constexpr TypeId typeId() noexcept
				{return TypeInfo<IntegerType>::id;}

			static constexpr Integer max() noexcept
				{return std::numeric_limits<Rep>::max();}

			static constexpr Integer min() noexcept
				{return std::numeric_limits<Rep>::min();}

			static constexpr Integer zero() noexcept
				{return Integer(static_cast<Rep>(0));}

			static constexpr Integer unity() noexcept
				{return Integer(static_cast<Rep>(1));}
		private:
			template<class Other>
			using EnableForUnsigned = std::enable_if<isUnsigned() && std::is_same<Integer,Other>::value,Other>;

			template<class Other>
			using EnableForSigned = std::enable_if<isSigned() && std::is_same<Integer,Other>::value,Other>;

		public:
			typedef IntegerType Rep;

			template<class U,std::enable_if_t<IsLosslessConvertible<U,IntegerType>::value && std::is_integral<U>::value,int> x=0>
			constexpr Integer(U value) noexcept:m_value(value)
				{}

			template<class U,std::enable_if_t<!IsLosslessConvertible<U,IntegerType>::value && std::is_integral<U>::value,int> x=0>
			constexpr explicit Integer(U value):m_value(narrow_cast<IntegerType>(value))
				{}

			template<class U,std::enable_if_t<IsLosslessConvertible<U,IntegerType>::value,int> x=0>
			constexpr Integer(Integer<U> value):m_value(static_cast<U>(value))
				{}

			template<class U,std::enable_if_t<!IsLosslessConvertible<U,IntegerType>::value,int> x=0>
			constexpr explicit Integer(Integer<U> value):m_value(narrow_cast<IntegerType>(static_cast<U>(value)))
				{}

			template<class Other>
			explicit constexpr operator Other() const
				{return cast_helper<Other>(m_value);}

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
				{return typename EnableForSigned<Other>::type(static_cast<Rep>(-m_value));}

			template<class Other=Integer>
			constexpr typename EnableForUnsigned<Other>::type operator~() const noexcept
				{return typename EnableForUnsigned<Other>::type(static_cast<Rep>(~m_value));}



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
		private:
			IntegerType m_value;
		};

	template<class IntegerType>
	struct IsUnsigned<Integer<IntegerType>>
		{static constexpr bool value = Integer<IntegerType>::isUnsigned();};


	template<class IntegralType>
	inline constexpr Integer<IntegralType> operator+(Integer<IntegralType> a, Integer<IntegralType> b) noexcept
		{return a+=b;}

	template<class IntegralType>
	inline constexpr Integer<IntegralType> operator-(Integer<IntegralType> a, Integer<IntegralType> b) noexcept
		{return a-=b;}

	template<class IntegralType>
	inline constexpr Integer<IntegralType> operator*(Integer<IntegralType> a, Integer<IntegralType> b) noexcept
		{return a*=b;}

	template<class IntegralType>
	inline constexpr Integer<IntegralType> operator/(Integer<IntegralType> a, Integer<IntegralType> b) noexcept
		{return a/=b;}

	template<class IntegralType>
	inline constexpr Integer<IntegralType> operator%(Integer<IntegralType> a, Integer<IntegralType> b) noexcept
		{return a%=b;}

	template<class IntegralType>
	inline constexpr Integer<IntegralType> operator<<(Integer<IntegralType> a, Integer<IntegralType> b) noexcept
		{return a<<=b;}

	template<class IntegralType>
	inline constexpr Integer<IntegralType> operator>>(Integer<IntegralType> a, Integer<IntegralType> b) noexcept
		{return a>>=b;}

	template<class IntegralType>
	inline constexpr Integer<IntegralType> operator|(Integer<IntegralType> a, Integer<IntegralType> b) noexcept
		{return a|=b;}

	template<class IntegralType>
	inline constexpr Integer<IntegralType> operator&(Integer<IntegralType> a, Integer<IntegralType> b) noexcept
		{return a&=b;}

	template<class IntegralType>
	inline constexpr Integer<IntegralType> operator^=(Integer<IntegralType> a, Integer<IntegralType> b) noexcept
		{return a^=b;}



	template<class Type,class IntegralType>
	inline constexpr std::enable_if_t<!IsLosslessConvertible<Integer<IntegralType>,Type>::value,bool>
	operator==(Type a, Integer<IntegralType> b) noexcept
		{return b==a;}

	template<class Type,class IntegralType>
	inline constexpr std::enable_if_t<!IsLosslessConvertible<Integer<IntegralType>,Type>::value,bool>
	operator!=(Type a, Integer<IntegralType> b) noexcept
		{return !(a==b);}

	template<class Type,class IntegralType>
	inline constexpr std::enable_if_t<!IsLosslessConvertible<Integer<IntegralType>,Type>::value,bool>
	operator<(Type a, Integer<IntegralType> b) noexcept
		{return b>a;}

	template<class Type,class IntegralType>
	inline constexpr std::enable_if_t<!IsLosslessConvertible<Integer<IntegralType>,Type>::value,bool>
	operator>(Type a, Integer<IntegralType> b) noexcept
		{return b<a;}

	template<class Type,class IntegralType>
	inline constexpr std::enable_if_t<!IsLosslessConvertible<Integer<IntegralType>,Type>::value,bool>
	operator<=(Type a, Integer<IntegralType> b) noexcept
		{return !(a>b);}

	template<class Type,class IntegralType>
	inline constexpr std::enable_if_t<!IsLosslessConvertible<Integer<IntegralType>,Type>::value,bool>
	operator>=(Type a, Integer<IntegralType> b) noexcept
		{return !(a<b);}
	}

#endif
