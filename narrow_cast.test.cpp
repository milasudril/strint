//@	{"targets":[{"name":"narrow_cast.test","type":"application","autorun":1}]}

#include "stic/stic.hpp"
#include "narrow_cast.hpp"

#include <limits>

STIC_TESTCASE("Signed to signed above max")
	{
	auto large_value = static_cast<int64_t>(std::numeric_limits<int32_t>::max()) + 1ll;
	STIC_ASSERT_THROW(Strint::narrow_cast<int32_t>(large_value); );

	large_value = std::numeric_limits<int16_t>::max() + 1ll;
	STIC_ASSERT_THROW(Strint::narrow_cast<int16_t>(large_value); );

	large_value = std::numeric_limits<int8_t>::max() + 1ll;
	STIC_ASSERT_THROW(Strint::narrow_cast<int8_t>(large_value); );
	STIC_ASSERT_NOTHROW(Strint::narrow_cast<int16_t>(large_value); );
	}

STIC_TESTCASE("Signed to signed below min")
	{
	auto large_value = static_cast<int64_t>(std::numeric_limits<int32_t>::min()) - 1ll;
	STIC_ASSERT_THROW(Strint::narrow_cast<int32_t>(large_value); );

	large_value = std::numeric_limits<int16_t>::min() - 1ll;
	STIC_ASSERT_THROW(Strint::narrow_cast<int16_t>(large_value); );

	large_value = std::numeric_limits<int8_t>::min() - 1ll;
	STIC_ASSERT_THROW(Strint::narrow_cast<int8_t>(large_value); );
	STIC_ASSERT_NOTHROW(Strint::narrow_cast<int16_t>(large_value); );
	}

STIC_TESTCASE("Unsigned to unsigned above max")
	{
	auto large_value = static_cast<uint64_t>(std::numeric_limits<uint32_t>::max()) + 1llu;
	STIC_ASSERT_THROW(Strint::narrow_cast<uint32_t>(large_value); );

	large_value = std::numeric_limits<uint16_t>::max() + 1llu;
	STIC_ASSERT_THROW(Strint::narrow_cast<uint16_t>(large_value); );

	large_value = std::numeric_limits<uint8_t>::max() + 1llu;
	STIC_ASSERT_THROW(Strint::narrow_cast<uint8_t>(large_value); );
	STIC_ASSERT_NOTHROW(Strint::narrow_cast<uint16_t>(large_value); );
	}

STIC_TESTCASE("Singned to unsigned To larger")
	{
	int32_t val = -1;
	STIC_ASSERT_THROW(Strint::narrow_cast<uint64_t>(val); );

	val = std::numeric_limits<int32_t>::max();
	STIC_ASSERT_NOTHROW(Strint::narrow_cast<uint32_t>(val););
	}

STIC_TESTCASE("Singned to unsigned To smaller")
	{
	int32_t val = -1;
	STIC_ASSERT_THROW(Strint::narrow_cast<uint16_t>(val); );

	val = std::numeric_limits<uint16_t>::max();
	STIC_ASSERT_NOTHROW(Strint::narrow_cast<uint64_t>(val); );

	val+=1;
	STIC_ASSERT_THROW(Strint::narrow_cast<uint16_t>(val); );
	}


STIC_TESTCASE("Unsingned to signed To smaller")
	{
	auto val = static_cast<uint32_t>( std::numeric_limits<int32_t>::max() ) + 1;
	STIC_ASSERT_THROW(Strint::narrow_cast<int32_t>(val); );

	val = std::numeric_limits<int32_t>::max();
	STIC_ASSERT_NOTHROW(Strint::narrow_cast<int32_t>(val););
	STIC_ASSERT_THROW(Strint::narrow_cast<int16_t>(val););

	val = std::numeric_limits<int16_t>::max();
	STIC_ASSERT_NOTHROW(Strint::narrow_cast<int16_t>(val););
	}
