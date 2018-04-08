//@	{"targets":[{"name":"traits.hpp","type":"include"}]}

#ifndef STRINT_TRAITS_HPP
#define STRINT_TRAITS_HPP

#include <type_traits>

namespace Strint
	{
	template<class T>
	struct IsUnsigned
		{static constexpr bool value = std::is_unsigned<T>::value;};

	template<class T>
	struct IsSigned
		{static constexpr bool value = !IsUnsigned<T>::value;};

	template<class IntegerTypeA, class IntegerTypeB>
	struct HasSameSignedness
		{
		static constexpr bool value=(IsSigned<IntegerTypeA>::value && IsSigned<IntegerTypeB>::value)
			|| (IsUnsigned<IntegerTypeA>::value && IsUnsigned<IntegerTypeB>::value);
		};

	template<class From, class To>
	struct IsLosslessConvertible
		{
		static constexpr bool value=HasSameSignedness<From,To>::value && sizeof(To)>=sizeof(From);
		};
	}
#endif
