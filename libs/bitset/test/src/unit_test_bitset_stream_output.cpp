/**
 *	@file	unit_test_bitset_stream_output.cpp
 *
 *	@brief	ストリームからの入力のテスト
 *
 *	template<class charT, class traits, size_t N>
 *	basic_ostream<charT, traits>&
 *	operator<<(basic_ostream<charT, traits>& os, const bitset<N>& x);
 */

#include <hamon/bitset.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"

GTEST_TEST(BitsetTest, StreamOutputTest)
{
	{
		std::ostringstream ss;
		const hamon::bitset<0> b0;
		ss << b0;
		EXPECT_EQ("", ss.str());
	}
	{
		std::ostringstream ss;
		const hamon::bitset<8> b0("00110110");
		ss << b0;
		EXPECT_EQ("00110110", ss.str());
	}
	{
		std::ostringstream ss;
		const hamon::bitset<64> b0("0101111101011111010111110101111101011111010111110101111101011111");
		ss << b0;
		EXPECT_EQ("0101111101011111010111110101111101011111010111110101111101011111", ss.str());
	}
}
