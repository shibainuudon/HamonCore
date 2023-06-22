/**
 *	@file	unit_test_bitset_xor.cpp
 *
 *	@brief	operator^ のテスト
 *
 *	template<size_t N>
 *	constexpr bitset<N> operator^(const bitset<N>& lhs, const bitset<N>& rhs) noexcept;
 */

#include <hamon/bitset.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(BitsetTest, XorTest)
{
	{
		HAMON_CXX11_CONSTEXPR auto b =
			hamon::bitset<0>() ^
			hamon::bitset<0>();
		EXPECT_EQ("", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, b.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b =
			hamon::bitset<1>("0") ^
			hamon::bitset<1>("0");
		EXPECT_EQ("0", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, b.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b =
			hamon::bitset<1>("1") ^
			hamon::bitset<1>("0");
		EXPECT_EQ("1", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x01u, b.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b =
			hamon::bitset<1>("0") ^
			hamon::bitset<1>("1");
		EXPECT_EQ("1", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x01u, b.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b =
			hamon::bitset<1>("1") ^
			hamon::bitset<1>("1");
		EXPECT_EQ("0", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, b.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b =
			hamon::bitset<7>("0101010") ^
			hamon::bitset<7>("0000111");
		EXPECT_EQ("0101101", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x2Du, b.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b =
			hamon::bitset<8>("01010101") ^
			hamon::bitset<8>("00001111");
		EXPECT_EQ("01011010", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x5Au, b.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b =
			hamon::bitset<9>("010111001") ^
			hamon::bitset<9>("000000000");
		EXPECT_EQ("010111001", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xB9u, b.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b =
			hamon::bitset<9>("010111001") ^
			hamon::bitset<9>("111111111");
		EXPECT_EQ("101000110", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x146u, b.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b =
			hamon::bitset<16>("0101010101010101") ^
			hamon::bitset<16>("0000111100001111");
		EXPECT_EQ("0101101001011010", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x5A5Au, b.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b =
			hamon::bitset<31>("1111111111111111111111111111111") ^
			hamon::bitset<31>("0100110001110000111100000111110");
		EXPECT_EQ("1011001110001111000011111000001", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x59C787C1u, b.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b =
			hamon::bitset<32>("01010101010101010101010101010101") ^
			hamon::bitset<32>("00001111000011110000111100001111");
		EXPECT_EQ("01011010010110100101101001011010", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x5A5A5A5Au, b.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b =
			hamon::bitset<33>("111111111111111111111111111111111") ^
			hamon::bitset<33>("010011000111000011110000011111000");
		EXPECT_EQ("101100111000111100001111100000111", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x1671E1F07u, b.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(18u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b =
			hamon::bitset<64>("0101010101010101010101010101010101010101010101010101010101010101") ^
			hamon::bitset<64>("0000111100001111000011110000111100001111000011110000111100001111");
		EXPECT_EQ("0101101001011010010110100101101001011010010110100101101001011010", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x5A5A5A5A5A5A5A5Au, b.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32u, b.count());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b =
			hamon::bitset<128>("01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101") ^
			hamon::bitset<128>("00001111000011110000111100001111000011110000111100001111000011110000111100001111000011110000111100001111000011110000111100001111");
		EXPECT_EQ("01011010010110100101101001011010010110100101101001011010010110100101101001011010010110100101101001011010010110100101101001011010", b.to_string());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(64u, b.count());
	}
}
