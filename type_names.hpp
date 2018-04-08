//@	{"targets":[{"name":"type_names.hpp","type":"include"}]}

#ifndef TYPE_TYPE_NAMES_HPP
#define TYPE_TYPE_NAMES_HPP

#include <cstdint>

namespace Type
	{
	template<class T>
	struct TypeInfo
		{};

	enum class TypeId:int
		{
		 Int8
		,UInt8
		,Int16
		,UInt16
		,Int32
		,UInt32
		,Int64
		,UInt64
		};

	template<>
	struct TypeInfo<int8_t>
		{
		static constexpr const char* name="i8";
		static constexpr auto id=TypeId::Int8;
		};

	template<>
	struct TypeInfo<int16_t>
		{
		static constexpr const char* name="i16";
		static constexpr auto id=TypeId::Int16;
		};

	template<>
	struct TypeInfo<int32_t>
		{
		static constexpr const char* name="i32";
		static constexpr auto id=TypeId::Int32;
		};

	template<>
	struct TypeInfo<int64_t>
		{
		static constexpr const char* name="i64";
		static constexpr auto id=TypeId::Int64;
		};



	template<>
	struct TypeInfo<uint8_t>
		{
		static constexpr const char* name="u8";
		static constexpr auto id=TypeId::UInt8;
		};

	template<>
	struct TypeInfo<uint16_t>
		{
		static constexpr const char* name="u16";
		static constexpr auto id=TypeId::UInt16;
		};

	template<>
	struct TypeInfo<uint32_t>
		{
		static constexpr const char* name="u32";
		static constexpr auto id=TypeId::UInt32;
		};

	template<>
	struct TypeInfo<uint64_t>
		{
		static constexpr const char* name="u64";
		static constexpr auto id=TypeId::UInt64;
		};
	}

#endif
