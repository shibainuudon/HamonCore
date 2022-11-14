/**
 *	@file	unit_test_bitflags_to_string.cpp
 *
 *	@brief	to_string関数のテスト
 */

#include <hamon/bitflags.hpp>
#include <gtest/gtest.h>
#include "bitflags_test.hpp"

namespace hamon_bitflags_test
{

GTEST_TEST(BitflagsTest, ToStringTest)
{
	{
		Bitflag1 const b;
		EXPECT_EQ("00000000000000000000000000000000", b.to_string());
	}
	{
		Bitflag1 const b(kOption1);
		EXPECT_EQ("00000000000000000000000000000001", b.to_string<char>());
	}
	{
		Bitflag1 const b(kOption2);
		EXPECT_EQ(L"00000000000000000000000000000010", b.to_string<wchar_t>());
	}
	{
		Bitflag1 const b =
			Bitflag1(kOption1) |
			Bitflag1(kOption3);
		EXPECT_EQ("00000000000000000000000000000101", b.to_string());
	}
	{
		Bitflag2 const b;
		EXPECT_EQ( "00000", b.to_string());
		EXPECT_EQ(L"00000", b.to_string<wchar_t>());
	}
	{
		Bitflag2 const b(Enum2::kOption4);
		EXPECT_EQ( "00001", b.to_string());
		EXPECT_EQ(L"****1", b.to_string(L'*'));
	}
	{
		Bitflag2 const b =
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption8);
		EXPECT_EQ("10101", b.to_string());
		EXPECT_EQ("XOXOX", b.to_string('O', 'X'));
	}
	{
		Bitflag3 const b;
		EXPECT_EQ( "0000000000000000", b.to_string());
		EXPECT_EQ(L"****************", b.to_string<wchar_t>(L'*'));
	}
	{
		Bitflag3 const b =
			Bitflag3(Enum3::kOption7) |
			Bitflag3(Enum3::kOption8) |
			Bitflag3(Enum3::kOption9);
		EXPECT_EQ( "0000000000110010", b.to_string());
		EXPECT_EQ(L"AAAAAAAAAA11AA1A", b.to_string(L'A'));
	}
}

}	// namespace hamon_bitflags_test
