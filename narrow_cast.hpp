//@	{"targets":[{"name":"narrow_cast.hpp","type":"include"}]}

#ifndef TYPE_NARROW_CAST_HPP
#define TYPE_NARROW_CAST_HPP

#include "exception_handler.hpp"
#include "traits.hpp"

#include <limits>

namespace Type
	{
	template<class To,class From>
	typename std::enable_if<HasSameSignedness<To,From>::value && sizeof(To)<sizeof(From), To>::type
	narrow_cast(From value)
		{
		if(std::numeric_limits<To>::min()<=value && std::numeric_limits<To>::max()>=value)
			{return To(value);}
		ExceptionHandler::castException(value);
		}

	template<class To, class From>
	typename std::enable_if<IsUnsigned<To>::value && IsSigned<From>::value && sizeof(To)>=sizeof(From),To>::type
	narrow_cast(From value)
		{
		if(value < 0)
			{ExceptionHandler::castException(value);}
		return To(value);
		}


	template<class To, class From>
	typename std::enable_if<IsUnsigned<To>::value && IsSigned<From>::value && sizeof(To)<sizeof(From),To>::type
	narrow_cast(From value)
		{
		return narrow_cast<To>(narrow_cast<typename std::make_unsigned<From>::type>(value));
		}

	template<class To, class From>
	typename std::enable_if<IsSigned<To>::value && IsUnsigned<From>::value && sizeof(To)<=sizeof(From),To>::type
	narrow_cast(From value)
		{
		if(value > std::numeric_limits<To>::max())
			{ExceptionHandler::castException(value);}
		return To(value);
		}

	}

#endif
