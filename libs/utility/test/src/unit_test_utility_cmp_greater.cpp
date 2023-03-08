/**
 *	@file	unit_test_utility_cmp_greater.cpp
 *
 *	@brief	cmp_greater のテスト
 */

#include <hamon/utility/cmp_greater.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(UtilityTest, CmpGreaterTest)
{
	HAMON_CXX11_CONSTEXPR hamon::int8_t   s08  = -1;
	HAMON_CXX11_CONSTEXPR hamon::int16_t  s16  = -1;
	HAMON_CXX11_CONSTEXPR hamon::int32_t  s32  = -1;
	HAMON_CXX11_CONSTEXPR hamon::int64_t  s64  = -1;
	HAMON_CXX11_CONSTEXPR hamon::uint8_t  u08  = (hamon::uint8_t )-1;
	HAMON_CXX11_CONSTEXPR hamon::uint16_t u16  = (hamon::uint16_t)-1;
	HAMON_CXX11_CONSTEXPR hamon::uint32_t u32  = (hamon::uint32_t)-1;
	HAMON_CXX11_CONSTEXPR hamon::uint64_t u64  = (hamon::uint64_t)-1;

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s08, s08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s08, s16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s08, s32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s08, s64));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s08, u08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s08, u16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s08, u32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s08, u64));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s16, s08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s16, s16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s16, s32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s16, s64));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s16, u08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s16, u16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s16, u32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s16, u64));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s32, s08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s32, s16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s32, s32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s32, s64));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s32, u08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s32, u16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s32, u32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s32, u64));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s64, s08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s64, s16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s64, s32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s64, s64));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s64, u08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s64, u16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s64, u32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(s64, u64));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u08, s08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u08, s16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u08, s32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u08, s64));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(u08, u08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(u08, u16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(u08, u32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(u08, u64));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u16, s08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u16, s16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u16, s32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u16, s64));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u16, u08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(u16, u16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(u16, u32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(u16, u64));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u32, s08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u32, s16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u32, s32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u32, s64));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u32, u08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u32, u16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(u32, u32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(u32, u64));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u64, s08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u64, s16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u64, s32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u64, s64));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u64, u08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u64, u16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(u64, u32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(u64, u64));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(0, 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(0, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_greater(1, 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_greater(1, 1));
}
