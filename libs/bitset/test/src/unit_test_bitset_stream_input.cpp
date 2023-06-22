/**
 *	@file	unit_test_bitset_stream_input.cpp
 *
 *	@brief	ストリームからの入力のテスト
 *
 *	template<class charT, class traits, size_t N>
 *	basic_istream<charT, traits>&
 *	operator>>(basic_istream<charT, traits>& is, bitset<N>& x);
 */

#include <hamon/bitset.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"

GTEST_TEST(BitsetTest, StreamInputTest)
{
	{
		std::istringstream ss("001101");

		hamon::bitset<0> b0;
		ss >> b0;
		EXPECT_EQ("", b0.to_string());
	}
	{
		std::istringstream ss("001101");

		hamon::bitset<3> b0;
		ss >> b0;
		EXPECT_EQ("001", b0.to_string());

		hamon::bitset<3> b1;
		ss >> b1;
		EXPECT_EQ("101", b1.to_string());
	}
	{
		std::istringstream ss("001101");

		hamon::bitset<8> b0;
		ss >> b0;
		EXPECT_EQ("00001101", b0.to_string());
	}
	{
		std::istringstream ss("0011X01");

		hamon::bitset<9> b0;
		ss >> b0;
		EXPECT_EQ("000000011", b0.to_string());
	}
	{
		std::istringstream ss("0101111101011111010111110101111101011111010111110101111101011111");

		hamon::bitset<64> b0;
		ss >> b0;
		EXPECT_EQ("0101111101011111010111110101111101011111010111110101111101011111", b0.to_string());
	}
}
