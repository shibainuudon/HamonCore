/**
 *	@file	unit_test_utility_in_range.cpp
 *
 *	@brief	in_range のテスト
 */

#include <hamon/utility/in_range.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(UtilityTest, InRangeTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::int8_t i = 0;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::int8_t i = -1;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::int8_t i = hamon::numeric_limits<hamon::int8_t>::min();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::int8_t i = hamon::numeric_limits<hamon::int8_t>::max();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::int16_t i = 0;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::int16_t i = -1;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::int16_t i = hamon::numeric_limits<hamon::int16_t>::min();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::int16_t i = hamon::numeric_limits<hamon::int16_t>::max();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::int32_t i = 0;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::int32_t i = -1;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::int32_t i = hamon::numeric_limits<hamon::int32_t>::min();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::int32_t i = hamon::numeric_limits<hamon::int32_t>::max();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::int64_t i = 0;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::int64_t i = -1;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::int64_t i = hamon::numeric_limits<hamon::int64_t>::min();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::int64_t i = hamon::numeric_limits<hamon::int64_t>::max();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::uint8_t i = hamon::numeric_limits<hamon::uint8_t>::min();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::uint8_t i = hamon::numeric_limits<hamon::uint8_t>::max();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::uint16_t i = hamon::numeric_limits<hamon::uint16_t>::min();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::uint16_t i = hamon::numeric_limits<hamon::uint16_t>::max();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::uint32_t i = hamon::numeric_limits<hamon::uint32_t>::min();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::uint32_t i = hamon::numeric_limits<hamon::uint32_t>::max();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::uint64_t i = hamon::numeric_limits<hamon::uint64_t>::min();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::uint64_t i = hamon::numeric_limits<hamon::uint64_t>::max();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<hamon::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<hamon::uint64_t>(i));
	}
}
