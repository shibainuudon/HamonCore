/**
 *	@file	unit_test_bitflags_output_stream.cpp
 *
 *	@brief	ストリームへの出力のテスト
 */

#include <hamon/bitflags.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "bitflags_test.hpp"

namespace hamon_bitflags_test
{

GTEST_TEST(BitflagsTest, OutputStreamTest)
{
	{
		Bitflag1 x;
		std::stringstream ss;
		ss << x;
		EXPECT_EQ("00000000000000000000000000000000", ss.str());
	}
	{
		Bitflag2 const x =
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption8);
		std::stringstream ss;
		ss << x;
		EXPECT_EQ("10111", ss.str());
	}
	{
		Bitflag2 x(Enum2::kOption4);
		std::wstringstream ss;
		ss << x;
		EXPECT_EQ(L"00001", ss.str());
	}
	{
		Bitflag3 const x =
			Bitflag3(Enum3::kOption7) |
			Bitflag3(Enum3::kOption9) |
			Bitflag3(Enum3::kOption8);
		std::wstringstream ss;
		ss << x;
		EXPECT_EQ(L"0000000000110010", ss.str());
	}
}

}	// namespace hamon_bitflags_test
