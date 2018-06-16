//@	{"targets":[{"name":"cast_exception.hpp","type":"include"}]}

#ifndef STRINT_CAST_EXCEPTION_HPP
#define STRINT_CAST_EXCEPTION_HPP

#include "message_formatter.hpp"

#include <limits>
#include <stdexcept>

namespace Strint
	{
	template<class To, class From>
	class CastException : public std::exception
		{
		public:
			explicit CastException(From value) noexcept: m_value(value)
				{}
			
			const char* what() const noexcept override
				{
				try
					{
					m_message = formatMessage(m_value, std::numeric_limits<To>::min()
						, std::numeric_limits<To>::max());
					return m_message.data();
					}
				catch(...)
					{return "Value out of range";}
				}
			
		private:
			From m_value;
			mutable std::string m_message;
		};
	}
#endif
