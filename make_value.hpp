//@	{"targets":[{"name":"make_value.hpp","type":"include"}]}

#ifndef STRINT_MAKE_VALUE_HPP
#define STRINT_MAKE_VALUE_HPP

namespace Strint
	{
	template<class T, class PrimitiveType>
	inline constexpr T make_value(PrimitiveType x)
		{return T{x};}

	template<class T>
	inline constexpr T make_default(typename T::Rep x={})
		{return make_value<T>(static_cast<typename T::Rep>(0));}
	}

#endif


