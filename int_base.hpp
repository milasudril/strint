//@	{"targets":[{"name":"int_base.hpp","type":"include"}]}

#ifndef STRINT_INTBASE_HPP
#define STRINT_INTBASE_HPP

#include "narrow_cast.hpp"
#include "type_names.hpp"

namespace Strint
	{
	template<class To, class From>
	inline constexpr
	std::enable_if_t<IsLosslessConvertible<From,To>::value,To>
	cast_helper(From val) noexcept
		{return static_cast<To>(val);}

	template<class IntegerType>
	class IntBase
		{
		public:
			typedef IntegerType Rep;

			constexpr IntBase()=default;

			template<class U,std::enable_if_t<IsLosslessConvertible<U,IntegerType>::value  && std::is_integral<U>::value,int> x=0>
			constexpr IntBase(U value) noexcept:m_value(value)
				{}

			template<class U,std::enable_if_t<!IsLosslessConvertible<U,IntegerType>::value && std::is_integral<U>::value,int> x=0>
			constexpr explicit IntBase(U value):m_value(narrow_cast<IntegerType>(value))
				{}

			template<class U,std::enable_if_t<IsLosslessConvertible<U,IntegerType>::value,int> x=0>
			constexpr IntBase(IntBase<U> value):m_value(static_cast<U>(value))
				{}

			template<class U,std::enable_if_t<!IsLosslessConvertible<U,IntegerType>::value,int> x=0>
			constexpr explicit IntBase(IntBase<U> value):m_value(narrow_cast<IntegerType>(static_cast<U>(value)))
				{}

			template<class Other>
			explicit constexpr operator Other() const
				{return cast_helper<Other>(m_value);}

			static constexpr bool isUnsigned() noexcept
				{return IsUnsigned<IntegerType>::value;}

			static constexpr bool isSigned() noexcept
				{return !isUnsigned();}

			static constexpr const char* typeName() noexcept
				{return TypeInfo<IntegerType>::name;}

			static constexpr TypeId typeId() noexcept
				{return TypeInfo<IntegerType>::id;}

		protected:
			IntegerType m_value;
		};

	template<class IntegerType>
	struct IsUnsigned<IntBase<IntegerType>>
		{static constexpr bool value = IntBase<IntegerType>::isUnsigned();};
	}

#endif
