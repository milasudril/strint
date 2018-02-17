//@	{"targets":[{"name":"integers.hpp","type":"include"}]}

#ifndef TYPE_INTEGERS_HPP
#define TYPE_INTEGERS_HPP

#include "narrow_cast.hpp"
#include <cstdint>
#include <cstddef>
#include <type_traits>

namespace Type
	{
	template<class IntegerTypeA, class IntegerTypeB>
	struct SameSign
		{
		static constexpr bool value=(std::is_signed<IntegerTypeA>::value && std::is_signed<IntegerTypeB>::value)
			|| (std::is_unsigned<IntegerTypeA>::value && std::is_unsigned<IntegerTypeB>::value) ;
		};

	template<class IntegerType>
	class IntBase
		{
		public:
			template<class U
				,typename std::enable_if<sizeof(U)<=sizeof(IntegerType) && SameSign<IntegerType,U>::value,int>::type x=1>
			constexpr IntBase(U value) noexcept:m_value(value){}

			template<class U
				,typename std::enable_if<!(sizeof(U)<=sizeof(IntegerType) && SameSign<IntegerType,U>::value),int>::type x=1>
			explicit IntBase(U value):m_value(narrow_cast<IntegerType>(value))
				{}


		private:
			IntegerType m_value;
		};
	}

#endif
