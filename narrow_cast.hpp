//@	{"targets":[{"name":"narrow_cast.hpp","type":"include"}]}

#ifndef TYPE_NARROW_CAST_HPP
#define TYPE_NARROW_CAST_HPP

#include "exception_handler.hpp"

namespace Type
	{
	template<class To,class From>
	To narrow_cast(From value)
		{
		To ret(value);
		From verify(ret);
		if(verify != value)
			{ExceptionHandler::castException(value);}
		return ret;
		}
	}

#endif
