/**
 *	@file	unit_test_utility_cmp_not_equal.cpp
 *
 *	@brief	cmp_not_equal のテスト
 */

#include <hamon/utility/cmp_not_equal.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include "constexpr_test.hpp"

GTEST_TEST(UtilityTest, CmpNotEqualTest)
{
	HAMON_CXX11_CONSTEXPR std::int8_t   s08  = -1;
	HAMON_CXX11_CONSTEXPR std::int16_t  s16  = -1;
	HAMON_CXX11_CONSTEXPR std::int32_t  s32  = -1;
	HAMON_CXX11_CONSTEXPR std::int64_t  s64  = -1;
	HAMON_CXX11_CONSTEXPR std::uint8_t  u08  = (std::uint8_t )-1;
	HAMON_CXX11_CONSTEXPR std::uint16_t u16  = (std::uint16_t)-1;
	HAMON_CXX11_CONSTEXPR std::uint32_t u32  = (std::uint32_t)-1;
	HAMON_CXX11_CONSTEXPR std::uint64_t u64  = (std::uint64_t)-1;

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(s08, s08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(s08, s16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(s08, s32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(s08, s64));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(s08, u08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(s08, u16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(s08, u32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(s08, u64));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(s16, s08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(s16, s16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(s16, s32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(s16, s64));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(s16, u08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(s16, u16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(s16, u32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(s16, u64));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(s32, s08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(s32, s16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(s32, s32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(s32, s64));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(s32, u08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(s32, u16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(s32, u32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(s32, u64));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(s64, s08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(s64, s16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(s64, s32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(s64, s64));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(s64, u08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(s64, u16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(s64, u32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(s64, u64));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u08, s08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u08, s16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u08, s32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u08, s64));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(u08, u08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u08, u16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u08, u32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u08, u64));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u16, s08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u16, s16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u16, s32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u16, s64));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u16, u08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(u16, u16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u16, u32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u16, u64));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u32, s08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u32, s16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u32, s32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u32, s64));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u32, u08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u32, u16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(u32, u32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u32, u64));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u64, s08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u64, s16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u64, s32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u64, s64));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u64, u08));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u64, u16));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(u64, u32));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(u64, u64));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(0, 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(0, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::cmp_not_equal(1, 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::cmp_not_equal(1, 1));
}
