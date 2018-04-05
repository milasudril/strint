//@	{"targets":[{"name":"int_base.hpp","type":"include"}]}

#ifndef TYPE_INTBASE_HPP
#define TYPE_INTBASE_HPP

#include "narrow_cast.hpp"

namespace Type
	{
	template<class To, class From>
	constexpr
	std::enable_if_t<IsLosslessConvertible<From,To>::value,To>
	cast_helper(From val) noexcept
		{return static_cast<To>(val);}

	template<class To, class From>
	constexpr
	std::enable_if_t<!IsLosslessConvertible<From,To>::value,To>
	cast_helper(From val)
		{return narrow_cast<To>(val);}

	template<class IntegerType>
	class IntBase
		{
		public:
			template<class U,std::enable_if_t<IsLosslessConvertible<U,IntegerType>::value,int> x=1>
			constexpr IntBase(U value) noexcept:m_value(value)
				{}

			template<class U,std::enable_if_t<!IsLosslessConvertible<U,IntegerType>::value,int> x=1>
			constexpr explicit IntBase(U value):m_value(narrow_cast<IntegerType>(value))
				{}

			template<class Other>
			explicit constexpr operator Other() const
				{return cast_helper<Other>(m_value);}

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
	}

#endif
