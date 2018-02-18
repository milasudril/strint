//@	{"targets":[{"name":"integers.hpp","type":"include"}]}

#ifndef TYPE_INTEGERS_HPP
#define TYPE_INTEGERS_HPP

#include "narrow_cast.hpp"
#include <cstdint>
#include <cstddef>
#include <type_traits>

namespace Type
	{
	template<class T>
	struct is_unsigned
		{
		static constexpr bool value = std::is_unsigned<T>::value;
		};

	template<class T>
	struct is_signed
		{
		static constexpr bool value = !is_unsigned<T>::value;
		};


	template<class IntegerTypeA, class IntegerTypeB>
	struct SameSign
		{
		static constexpr bool value=(is_signed<IntegerTypeA>::value && is_signed<IntegerTypeB>::value)
			|| (is_unsigned<IntegerTypeA>::value && is_unsigned<IntegerTypeB>::value) ;
		};

	template<class IntegerType>
	class IntBase
		{
		public:
			template<class U
				,typename std::enable_if<sizeof(U)<=sizeof(IntegerType) && SameSign<IntegerType,U>::value,int>::type x=1>
			constexpr IntBase(U value) noexcept:m_value(value)
				{}

			template<class U
				,typename std::enable_if<!(sizeof(U)<=sizeof(IntegerType) && SameSign<IntegerType,U>::value),int>::type x=1>
			explicit IntBase(U value):m_value(narrow_cast<IntegerType>(value))
				{}

			constexpr operator IntegerType() const noexcept
				{return m_value;}

			static constexpr bool is_unsigned=is_unsigned<IntegerType>::value;

		private:
			IntegerType m_value;
		};

	template<class IntegerType>
	struct is_unsigned<IntBase<IntegerType>>
		{
		static constexpr bool value = IntBase<IntegerType>::is_unsigned;
		};

//	template<> using is_signed<IntBase> = std::is_signed<T>;

	template<size_t N>
	class Int;


	template<>
	class Int<8>:public IntBase<int8_t>
		{
		public:
			using IntBase<int8_t>::IntBase;
		};

	template<>
	class Int<16>:public IntBase<int16_t>
		{
		public:
			using IntBase<int16_t>::IntBase;
		};

	template<>
	class Int<32>:public IntBase<int32_t>
		{
		public:
			using IntBase<int32_t>::IntBase;
		};

	template<>
	class Int<64>:public IntBase<int64_t>
		{
		public:
			using IntBase<int64_t>::IntBase;
		};

	}

#endif
