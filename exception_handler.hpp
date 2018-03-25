//@	{"targets":[{"name":"exception_handler.hpp","type":"include"}]}

#ifndef TYPE_EXCEPTION_HANDLER_HPP
#define TYPE_EXCEPTION_HANDLER_HPP

#include "error_message.hpp"

namespace Type
	{
	class ExceptionHandler
		{
		public:
			template<class U>
			[[noreturn]] static void castException(U value)
				{raise(ErrorMessage(value, " cannot be represented internally."));}

		private:
			[[noreturn]] static void raise(const ErrorMessage& message)
				{throw message;}
		};
	}

#endif
