//@	{"targets":[{"name":"exception_handler.hpp","type":"include"}]}

#ifndef TYPE_EXCEPTION_HANDLER_HPP
#define TYPE_EXCEPTION_HANDLER_HPP

#include <array>

namespace Type
	{
	typedef std::array<char, 512> ErrorMessage;

	typedef void (*ExceptionFunction)(const ErrorMessage& message);

	class ExceptionHandler
		{
		public:
			template<class U>
			static void castException(U value)
				{raise(ErrorMessage("#0 cannot be represented internally", value));}

		private:
			static void raise(const ErrorMessage& message);
		};
	}

#endif
