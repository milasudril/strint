//@	{"targets":[{"name":"type_names.hpp","type":"include"}]}

#ifndef STRINT_STRINT_NAMES_HPP
#define STRINT_STRINT_NAMES_HPP

#include <cstdint>

namespace Strint
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
		static constexpr const char* name="i10";
		static constexpr auto id=TypeId::Int16;
		};

	template<>
	struct TypeInfo<int32_t>
		{
		static constexpr const char* name="i20";
		static constexpr auto id=TypeId::Int32;
		};

	template<>
	struct TypeInfo<int64_t>
		{
		static constexpr const char* name="i40";
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
		static constexpr const char* name="u10";
		static constexpr auto id=TypeId::UInt16;
		};

	template<>
	struct TypeInfo<uint32_t>
		{
		static constexpr const char* name="u20";
		static constexpr auto id=TypeId::UInt32;
		};

	template<>
	struct TypeInfo<uint64_t>
		{
		static constexpr const char* name="u40";
		static constexpr auto id=TypeId::UInt64;
		};
	}

#endif
