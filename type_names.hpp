//@	{"targets":[{"name":"type_names.hpp","type":"include"}]}

#ifndef TYPE_TYPE_NAMES_HPP
#define TYPE_TYPE_NAMES_HPP

#include <cstdint>

namespace Type
	{
	template<class T>
	struct TypeName
		{};


	template<>
	struct TypeName<int8_t>
		{static constexpr const char* value="i8";};

	template<>
	struct TypeName<int16_t>
		{static constexpr const char* value="i16";};

	template<>
	struct TypeName<int32_t>
		{static constexpr const char* value="i32";};

	template<>
	struct TypeName<int64_t>
		{static constexpr const char* value="i64";};



	template<>
	struct TypeName<uint8_t>
		{static constexpr const char* value="u8";};

	template<>
	struct TypeName<uint16_t>
		{static constexpr const char* value="u16";};

	template<>
	struct TypeName<uint32_t>
		{static constexpr const char* value="u32";};

	template<>
	struct TypeName<uint64_t>
		{static constexpr const char* value="u64";};
	}

#endif
