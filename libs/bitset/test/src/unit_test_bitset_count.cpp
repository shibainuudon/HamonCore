/**
 *	@file	unit_test_bitset_count.cpp
 *
 *	@brief	count関数のテスト
 *
 *	constexpr size_t count() const noexcept;
 */

#include <hamon/bitset.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(BitsetTest, CountTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<0> b;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<0>();
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<7>();
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<8> b;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<8>();
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<8> b("10110001");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<9>();
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(9u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<63>();
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(63u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b("0101111101011111010111110101111101011111010111110101111101011111");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(48u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = hamon::bitset<65>();
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<65>();
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(65u, b.count());
	}
}
