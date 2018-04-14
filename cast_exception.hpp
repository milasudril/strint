//@	{"targets":[{"name":"cast_exception.hpp","type":"include"}]}

#ifndef STRINT_CAST_EXCEPTION_HPP
#define STRINT_CAST_EXCEPTION_HPP

#include "message_formatter.hpp"
#include <type_traits>
#include <stdexcept>

namespace Strint
	{
	class CastException : public std::runtime_error
		{
		public:
			template<class From, class To>
			explicit CastException(From value, To min, To max) noexcept:
				std::runtime_error(formatMessage(value, min, max))
				{}
		};
	}
#endif
