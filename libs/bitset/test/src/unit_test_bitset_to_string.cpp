/**
 *	@file	unit_test_bitset_to_string.cpp
 *
 *	@brief	to_string関数のテスト
 *
 *	template<class charT = char,
 *		class traits = char_traits<charT>,
 *		class Allocator = allocator<charT>>
 *	constexpr basic_string<charT, traits, Allocator>
 *	to_string(charT zero = charT('0'), charT one = charT('1')) const;
 */

#include <hamon/bitset.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(BitsetTest, ToStringTest)
{
	{
		const hamon::bitset<0> b;
		EXPECT_EQ("", b.to_string());
		EXPECT_EQ("", b.to_string('*'));
	}
	{
		const hamon::bitset<8> b("10110001");
		EXPECT_EQ("10110001", b.to_string());
		EXPECT_EQ("1*11***1", b.to_string('*'));
		EXPECT_EQ("BABBAAAB", b.to_string('A', 'B'));
	}
	{
		const hamon::bitset<64> b("0101111101011111010111110101111101011111010111110101111101011111");
		EXPECT_EQ("0101111101011111010111110101111101011111010111110101111101011111", b.to_string());
		EXPECT_EQ(" 1 11111 1 11111 1 11111 1 11111 1 11111 1 11111 1 11111 1 11111", b.to_string(' '));
		EXPECT_EQ("._._____._._____._._____._._____._._____._._____._._____._._____", b.to_string('.', '_'));
	}
}
