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
			static void castException(U value)
				{raise(ErrorMessage("cannot be represented internally"));}

		private:
			static void raise(const ErrorMessage& message)
				{fprintf(stderr,"%s\n", message.c_str());abort();}
		};
	}

#endif
