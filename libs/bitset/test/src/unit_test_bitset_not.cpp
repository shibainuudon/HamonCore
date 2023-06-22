/**
 *	@file	unit_test_bitset_not.cpp
 *
 *	@brief	operator~ のテスト
 *
 *	constexpr bitset operator~() const noexcept;
 */

#include <hamon/bitset.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(BitsetTest, NotTest)
{
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<0>();
		EXPECT_EQ("", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<1>();
		EXPECT_EQ("1", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<1>("1");
		EXPECT_EQ("0", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<7>();
		EXPECT_EQ("1111111", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(127u, b.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<8>();
		EXPECT_EQ("11111111", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(255u, b.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<9>();
		EXPECT_EQ("111111111", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(511u, b.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(9u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<8>("01011111");
		EXPECT_EQ("10100000", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(160u, b.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<16>();
		EXPECT_EQ("1111111111111111", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFFFu, b.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<16>("0101111101011111");
		EXPECT_EQ("1010000010100000", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xA0A0u, b.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<32>("01011111010111110101111101011111");
		EXPECT_EQ("10100000101000001010000010100000", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xA0A0A0A0u, b.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<40>();
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(40u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<41>();
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(41u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<64>("0101111101011111010111110101111101011111010111110101111101011111");
		EXPECT_EQ("1010000010100000101000001010000010100000101000001010000010100000", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xA0A0A0A0A0A0A0A0u, b.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<127>();
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(127u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<128>();
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(128u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<128>("01011111010111110101111101011111010111110101111101011111010111110101111101011111010111110101111101011111010111110101111101011111");
		EXPECT_EQ("10100000101000001010000010100000101000001010000010100000101000001010000010100000101000001010000010100000101000001010000010100000", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<129>();
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(129u, b.count());
	}
}
