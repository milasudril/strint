//@	{"targets":[{"name":"integers.hpp","type":"include"}]}

#ifndef TYPE_INTEGERS_HPP
#define TYPE_INTEGERS_HPP

#include <cstdint>
#include <cstddef>

namespace Type
	{
	template<size_t N> class Int{};

	template<class T>
	class IntBase{};

	template<>
	class Int<32>:public IntBase<int32_t>{};
	}

#endif
