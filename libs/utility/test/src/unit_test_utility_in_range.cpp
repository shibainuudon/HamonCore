/**
 *	@file	unit_test_utility_in_range.cpp
 *
 *	@brief	in_range のテスト
 */

#include <hamon/utility/in_range.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include <cstdint>
#include "constexpr_test.hpp"

GTEST_TEST(UtilityTest, InRangeTest)
{
	{
		HAMON_CXX11_CONSTEXPR std::int8_t i = 0;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::int8_t i = -1;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::int8_t i = std::numeric_limits<std::int8_t>::min();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::int8_t i = std::numeric_limits<std::int8_t>::max();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::int16_t i = 0;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::int16_t i = -1;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::int16_t i = std::numeric_limits<std::int16_t>::min();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::int16_t i = std::numeric_limits<std::int16_t>::max();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::int32_t i = 0;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::int32_t i = -1;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::int32_t i = std::numeric_limits<std::int32_t>::min();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::int32_t i = std::numeric_limits<std::int32_t>::max();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::int64_t i = 0;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::int64_t i = -1;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::int64_t i = std::numeric_limits<std::int64_t>::min();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::int64_t i = std::numeric_limits<std::int64_t>::max();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::uint8_t i = std::numeric_limits<std::uint8_t>::min();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::uint8_t i = std::numeric_limits<std::uint8_t>::max();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::uint16_t i = std::numeric_limits<std::uint16_t>::min();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::uint16_t i = std::numeric_limits<std::uint16_t>::max();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::uint32_t i = std::numeric_limits<std::uint32_t>::min();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::uint32_t i = std::numeric_limits<std::uint32_t>::max();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::uint64_t i = std::numeric_limits<std::uint64_t>::min();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint64_t>(i));
	}
	{
		HAMON_CXX11_CONSTEXPR std::uint64_t i = std::numeric_limits<std::uint64_t>::max();
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::int64_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint8_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint16_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::in_range<std::uint32_t>(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::in_range<std::uint64_t>(i));
	}
}
