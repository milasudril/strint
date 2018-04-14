//@	{"targets":[{"name":"message_formatter.test.cpp", "type":"application","autorun":1}]}

#include "message_formatter.hpp"

#include "stic/stic.hpp"

STIC_TESTCASE("Default message")
	{
	STIC_ASSERT(Strint::formatMessage(0, 1, 2) == "Value out of range");
	}

namespace
	{
	class TestFormatter
		{
		public:
			template<class Value, class Boundary>
			std::string valueOutOfRange(Value val, Boundary min, Boundary max) const
				{
				return std::string("Value ")
					+ std::to_string(val)
					+ std::string(" is out of range [")
					+ std::to_string(min) + ", "
					+ std::to_string(max) + "]";
				}
		};
	}

STIC_TESTCASE("Custom message")
	{
	Strint::messageFormatter(TestFormatter{});
	STIC_ASSERT(Strint::formatMessage(0, 1, 2) == "Value 0 is out of range [1, 2]");

	STIC_ASSERT(Strint::formatMessage(-3, 0u, 2u) == "Value -3 is out of range [0, 2]");
	}

