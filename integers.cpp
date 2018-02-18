//@	{"targets":[{"name":"integers.test","type":"application"}]}

#include "integers.hpp"

int main()
	{
	Type::Int<8> foo(static_cast<int8_t>(112));

	Type::Int<16> bar(foo);

	int8_t val=123;
	foo=val;

	Type::Int<8,Type::Signedness::Unsigned> flags(uint8_t(0));
	flags|=uint8_t(0xff);

	}
