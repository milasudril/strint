//@	{"targets":[{"name":"error_message.hpp","type":"include"}]}

#ifndef TYPE_ERROR_MESSAGE_HPP
#define TYPE_ERROR_MESSAGE_HPP

#include <array>

namespace Type
	{
	class ErrorMessage
		{
		public:
			template<class First, class ... T>
			explicit ErrorMessage(First&& first,T ... values) noexcept
				{
				formatMessage(m_message.begin(), m_message.end(), std::forward<First>(first), values...);
				}

			const char* c_str() const noexcept
				{return m_message.begin();}

		private:
			static char* format(char* begin, char* end, const char* str) noexcept
				{
				while(begin!=end - 1)
					{
					auto ch_in=*str;
					if(ch_in==0)
						{return begin;}
					*begin=ch_in;
					++begin;
					++str;
					}
				return begin;
				}

			static char* formatMessage(char* begin,char*) noexcept
				{
				*begin='\0';
				return begin;
				}


			template<class Value,class ... Args>
			static char* formatMessage(char* begin, char* end, Value&& val, Args ... values) noexcept
				{
				if(begin == end - 1)
					{
					*begin='\0';
					return begin;
					}
				begin=format(begin, end, std::forward<Value>(val));
				begin=formatMessage(begin, end, values...);
				return begin;
				}
			std::array<char, 512> m_message;
		};
	}

#endif
