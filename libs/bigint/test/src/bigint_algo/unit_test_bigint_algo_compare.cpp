/**
 *	@file	unit_test_bigint_algo_compare.cpp
 *
 *	@brief	bigint_algo::compare のテスト
 */

#include <hamon/bigint/bigint_algo/compare.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

GTEST_TEST(BigIntAlgoTest, CompareTest)
{
	{
		std::vector<hamon::uint8_t> const a{0};
		std::vector<hamon::uint8_t> const b{0};
		EXPECT_EQ( 0, hamon::bigint_algo::compare(a, b));
		EXPECT_EQ( 0, hamon::bigint_algo::compare(b, a));
	}
	{
		std::vector<hamon::uint8_t> const a{0};
		std::vector<hamon::uint8_t> const b{1};
		EXPECT_EQ(-1, hamon::bigint_algo::compare(a, b));
		EXPECT_EQ( 1, hamon::bigint_algo::compare(b, a));
	}
	{
		std::vector<hamon::uint8_t> const a{1};
		std::vector<hamon::uint8_t> const b{1};
		EXPECT_EQ( 0, hamon::bigint_algo::compare(a, b));
		EXPECT_EQ( 0, hamon::bigint_algo::compare(b, a));
	}
	{
		std::vector<hamon::uint8_t> const a{0x00, 0x10};
		std::vector<hamon::uint8_t> const b{0xFF};
		EXPECT_EQ( 1, hamon::bigint_algo::compare(a, b));
		EXPECT_EQ(-1, hamon::bigint_algo::compare(b, a));
	}
	{
		std::vector<hamon::uint8_t> const a{0x00, 0x10};
		std::vector<hamon::uint8_t> const b{0xFF, 0x0F};
		EXPECT_EQ( 1, hamon::bigint_algo::compare(a, b));
		EXPECT_EQ(-1, hamon::bigint_algo::compare(b, a));
	}

	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> const a{0};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> const b{0};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::bigint_algo::compare(a, b));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::bigint_algo::compare(b, a));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> const a{0x12, 0x34, 0x56, 0x78};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> const b{0xFF, 0xFF, 0xFF, 0xFF};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, hamon::bigint_algo::compare(a, b));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::bigint_algo::compare(b, a));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> const a{0x12, 0x34, 0x56, 0x78};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> const b{0xFF, 0xFF, 0xFF, 0x00};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::bigint_algo::compare(a, b));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, hamon::bigint_algo::compare(b, a));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> const a{0x12, 0x34, 0x56, 0x78};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> const b{0x13, 0x34, 0x56, 0x78};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, hamon::bigint_algo::compare(a, b));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::bigint_algo::compare(b, a));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> const a{0x12, 0x34, 0x56, 0x78};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> const b{0x12, 0x34, 0x56, 0x78};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::bigint_algo::compare(a, b));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::bigint_algo::compare(b, a));
	}
}
