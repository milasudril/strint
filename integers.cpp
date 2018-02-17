//@	{"targets":[{"name":"integers.test","type":"application"}]}

#include "integers.hpp"

int main()
	{
	Type::IntBase<int8_t> foo(static_cast<int8_t>(112));
	Type::IntBase<int8_t> foo_bar(1234);
	}
