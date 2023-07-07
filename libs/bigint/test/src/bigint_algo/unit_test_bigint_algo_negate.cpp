/**
 *	@file	unit_test_bigint_algo_negate.cpp
 *
 *	@brief	bigint_algo::negate のテスト
 */

#include <hamon/bigint/bigint_algo/negate.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

GTEST_TEST(BigIntAlgoTest, NegateTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> const a{0x00};
		HAMON_CXX11_CONSTEXPR auto const b = hamon::detail::bigint_algo::negate(a);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, b[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, b[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, b[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, b[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> const a{0x01};
		HAMON_CXX11_CONSTEXPR auto const b = hamon::detail::bigint_algo::negate(a);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFu, b[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFu, b[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFu, b[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFu, b[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> const a{0xFF, 0xFF, 0xFF, 0xFF};
		HAMON_CXX11_CONSTEXPR auto const b = hamon::detail::bigint_algo::negate(a);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x01u, b[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, b[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, b[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, b[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> const a{0x12, 0x34, 0x56, 0x78};
		HAMON_CXX11_CONSTEXPR auto const b = hamon::detail::bigint_algo::negate(a);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xEEu, b[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xCBu, b[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xA9u, b[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x87u, b[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 3> const a{0x0002};
		HAMON_CXX11_CONSTEXPR auto const b = hamon::detail::bigint_algo::negate(a);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFFEu, b[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFFFu, b[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFFFu, b[2]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 2> const a{0xFFFF, 0xFFFF};
		HAMON_CXX11_CONSTEXPR auto const b = hamon::detail::bigint_algo::negate(a);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0001u, b[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, b[1]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 3> const a{0x1234, 0x5678, 0x9ABC};
		HAMON_CXX11_CONSTEXPR auto const b = hamon::detail::bigint_algo::negate(a);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xEDCCu, b[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xA987u, b[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x6543u, b[2]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint32_t, 1> const a{0};
		HAMON_CXX11_CONSTEXPR auto const b = hamon::detail::bigint_algo::negate(a);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00000000u, b[0]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint32_t, 3> const a{0x12345678, 0x9ABCDEF0};
		HAMON_CXX11_CONSTEXPR auto const b = hamon::detail::bigint_algo::negate(a);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xEDCBA988u, b[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x6543210Fu, b[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFFFFFFFu, b[2]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint64_t, 2> const a{0x123456789ABCDEF0};
		HAMON_CXX11_CONSTEXPR auto const b = hamon::detail::bigint_algo::negate(a);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xEDCBA98765432110u, b[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFFFFFFFFFFFFFFFu, b[1]);
	}
}
