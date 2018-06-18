//@	{"targets":[{"name":"message_formatter.hpp","type":"include"}]}

#ifndef STRINT_MESSAGE_FORMATTER_HPP
#define STRINT_MESSAGE_FORMATTER_HPP

#include <string>
#include <cstdint>
#include <memory>

namespace Strint
	{
	class MessageFormatterBase
		{
		public:
			virtual std::string valueOutOfRange(intmax_t value, intmax_t min, intmax_t max) const = 0;
			virtual std::string valueOutOfRange(intmax_t value, uintmax_t min, uintmax_t max) const = 0;
			virtual std::string valueOutOfRange(uintmax_t value, intmax_t min, intmax_t max) const = 0;
			virtual std::string valueOutOfRange(uintmax_t value, uintmax_t min, uintmax_t max) const = 0;
			virtual ~MessageFormatterBase() = default;
		};

	template<class Formatter>
	class MessageFormatter final:public MessageFormatterBase
		{
		public:
			explicit MessageFormatter(Formatter&& fmt) : m_formatter(std::forward<Formatter>(fmt))
				{}

			std::string valueOutOfRange(intmax_t value, intmax_t min, intmax_t max) const override
				{return m_formatter.valueOutOfRange(value, min, max);}
			std::string valueOutOfRange(intmax_t value, uintmax_t min, uintmax_t max) const override
				{return m_formatter.valueOutOfRange(value, min, max);}
			std::string valueOutOfRange(uintmax_t value, intmax_t min, intmax_t max) const override
				{return m_formatter.valueOutOfRange(value, min, max);}
			std::string valueOutOfRange(uintmax_t value, uintmax_t min, uintmax_t max) const override
				{return m_formatter.valueOutOfRange(value, min, max);}

		private:
			Formatter m_formatter;
		};

	template<class From, class To>
	inline std::string formatMessage(From value, To min, To max);

	template<class Formatter>
	inline void messageFormatter(Formatter&& formatter) noexcept;

	namespace detail
		{
		template<bool is_unsigned>
		using LargestType = typename std::conditional<is_unsigned, uintmax_t, intmax_t>::type;

		template<class Dummy=void>
		struct FormatCaller
			{
			public:
				template<class From, class To>
				static std::string formatMessage(From value, To min, To max)
					{
					return s_formatter?
						s_formatter->valueOutOfRange(static_cast<LargestType<std::is_unsigned<From>::value>>(value)
							, static_cast<LargestType<std::is_unsigned<To>::value>>(min)
							, static_cast<LargestType<std::is_unsigned<To>::value>>(max))
						: "Value out of range";
					}

				template<class Formatter>
				static void formatter(Formatter&& fmt) noexcept
					{s_formatter = std::make_unique<MessageFormatter<Formatter> const>(std::forward<Formatter>(fmt));}

			private:
				static std::unique_ptr<MessageFormatterBase const> s_formatter;
			};

		template<class Dummy>
		std::unique_ptr<MessageFormatterBase const> FormatCaller<Dummy>::s_formatter = nullptr;
		}

	template<class From, class To>
	inline std::string formatMessage(From value, To min, To max)
		{return detail::FormatCaller<>::formatMessage(value, min, max);}

	template<class Formatter>
	inline void messageFormatter(Formatter&& formatter) noexcept
		{detail::FormatCaller<>::formatter(std::forward<Formatter>(formatter));}
	}
#endif
