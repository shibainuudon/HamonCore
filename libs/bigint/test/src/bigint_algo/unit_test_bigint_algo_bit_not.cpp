/**
 *	@file	unit_test_bigint_algo_bit_not.cpp
 *
 *	@brief	bigint_algo::bit_not のテスト
 */

#include <hamon/bigint/bigint_algo/bit_not.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

GTEST_TEST(BigIntAlgoTest, BitNotTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> const a{0x12, 0x34, 0x56, 0x78};
		HAMON_CXX11_CONSTEXPR auto const b = hamon::bigint_algo::bit_not(a);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xEDu, b[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xCBu, b[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xA9u, b[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x87u, b[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 3> const a{0x1234, 0x5678, 0x9ABC};
		HAMON_CXX11_CONSTEXPR auto const b = hamon::bigint_algo::bit_not(a);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xEDCBu, b[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xA987u, b[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x6543u, b[2]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint32_t, 3> const a{0x12345678, 0x9ABCDEF0};
		HAMON_CXX11_CONSTEXPR auto const b = hamon::bigint_algo::bit_not(a);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xEDCBA987u, b[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x6543210Fu, b[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFFFFFFFu, b[2]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint64_t, 2> const a{0x123456789ABCDEF0};
		HAMON_CXX11_CONSTEXPR auto const b = hamon::bigint_algo::bit_not(a);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xEDCBA9876543210Fu, b[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFFFFFFFFFFFFFFFu, b[1]);
	}
}
