//@	{"targets":[{"name":"make_value.test","type":"application","autorun":1}]}

#include "make_value.hpp"
#include "integer.hpp"
#include "stic/stic.hpp"

STIC_TESTCASE("Make defualt value")
	{
	auto val = Strint::make_default<Strint::Integer<short>>();

	STIC_ASSERT(val == static_cast<short>(0));
	}

STIC_TESTCASE("Make value")
	{
	auto val = Strint::make_value<Strint::Integer<int>>(123);
	STIC_ASSERT(val == 123);
	}
