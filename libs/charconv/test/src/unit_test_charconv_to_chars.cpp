/**
 *	@file	unit_test_charconv_to_chars.cpp
 *
 *	@brief	to_chars のテスト
 */

#include <hamon/charconv/to_chars.hpp>
#include <hamon/string_view.hpp>
#include <hamon/system_error/errc.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_charconv_test
{

namespace to_chars_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool
ToCharsResultTest()
{
	char buf[128]{};

	hamon::to_chars_result res1{buf, hamon::errc{}};
	hamon::to_chars_result res2{buf, hamon::errc{}};
	hamon::to_chars_result res3{buf, hamon::errc::value_too_large};
	hamon::to_chars_result res4{buf+1, hamon::errc{}};
	hamon::to_chars_result res5{buf+1, hamon::errc::value_too_large};

	VERIFY( (res1 == res1));
	VERIFY( (res1 == res2));
	VERIFY(!(res1 == res3));
	VERIFY(!(res1 == res4));
	VERIFY(!(res1 == res5));

	VERIFY(!(res1 != res1));
	VERIFY(!(res1 != res2));
	VERIFY( (res1 != res3));
	VERIFY( (res1 != res4));
	VERIFY( (res1 != res5));

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
IntegerToCharsTest(T val, int base, const char* expected)
{
	char buf[128]{};
	auto ret = hamon::to_chars(buf, buf+sizeof(buf), val, base);
	VERIFY(hamon::string_view(buf, ret.ptr) == expected);
	VERIFY(ret.ec == hamon::errc{});

	return true;
}

GTEST_TEST(CharConvTest, ToCharsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToCharsResultTest());

	// 10進
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(0, 10, "0"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(1, 10, "1"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(-1, 10, "-1"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(10, 10, "10"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(-42, 10, "-42"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(123, 10, "123"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(-128, 10, "-128"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(255, 10, "255"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(-32768, 10, "-32768"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(65536, 10, "65536"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(0xFFFFFFFF, 10, "4294967295"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(0xFFFFFFFFFFFFFFFF, 10, "18446744073709551615"));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(       100, 10, "100"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(      1000, 10, "1000"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(     10000, 10, "10000"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(    100000, 10, "100000"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(   1000000, 10, "1000000"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(  10000000, 10, "10000000"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest( 100000000, 10, "100000000"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(1000000000, 10, "1000000000"));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(       -100, 10, "-100"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(      -1000, 10, "-1000"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(     -10000, 10, "-10000"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(    -100000, 10, "-100000"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(   -1000000, 10, "-1000000"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(  -10000000, 10, "-10000000"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest( -100000000, 10, "-100000000"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(-1000000000, 10, "-1000000000"));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(         9, 10, "9"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(        99, 10, "99"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(       999, 10, "999"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(      9999, 10, "9999"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(     99999, 10, "99999"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(    999999, 10, "999999"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(   9999999, 10, "9999999"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(  99999999, 10, "99999999"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest( 999999999, 10, "999999999"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(9999999999, 10, "9999999999"));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(         -9, 10, "-9"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(        -99, 10, "-99"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(       -999, 10, "-999"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(      -9999, 10, "-9999"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(     -99999, 10, "-99999"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(    -999999, 10, "-999999"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(   -9999999, 10, "-9999999"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(  -99999999, 10, "-99999999"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest( -999999999, 10, "-999999999"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(-9999999999, 10, "-9999999999"));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest((signed   char)     123, 10, "123"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest((unsigned char)     123, 10, "123"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest((signed   short)    123, 10, "123"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest((unsigned short)    123, 10, "123"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest((signed   long)     123, 10, "123"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest((unsigned long)     123, 10, "123"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest((signed   long long)123, 10, "123"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest((unsigned long long)123, 10, "123"));

	// 2進
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(0, 2, "0"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(1, 2, "1"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(-1, 2, "-1"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(10, 2, "1010"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(-42, 2, "-101010"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(123, 2, "1111011"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(-128, 2, "-10000000"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(255, 2, "11111111"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(-32768, 2, "-1000000000000000"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(65536, 2, "10000000000000000"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(0xFFFFFFFF, 2, "11111111111111111111111111111111"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(0xFFFFFFFFFFFFFFFF, 2, "1111111111111111111111111111111111111111111111111111111111111111"));

	// 2進～36進
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 2, "11000000111001"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 3, "121221020"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 4, "3000321"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 5, "343340"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 6, "133053"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 7, "50664"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 8, "30071"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 9, "17836"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 10, "12345"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 11, "9303"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 12, "7189"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 13, "5808"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 14, "46db"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 15, "39d0"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 16, "3039"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 17, "28c3"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 18, "221f"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 19, "1f3e"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 20, "1ah5"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 21, "16ki"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 22, "13b3"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 23, "107h"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 24, "la9"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 25, "jik"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 26, "i6l"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 27, "gp6"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 28, "fkp"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 29, "ejk"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 30, "dlf"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 31, "cq7"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 32, "c1p"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 33, "bb3"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 34, "an3"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 35, "a2p"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12345, 36, "9ix"));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(10, 11, "a"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(11, 12, "b"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(12, 13, "c"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(13, 14, "d"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(14, 15, "e"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(15, 16, "f"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(16, 17, "g"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(17, 18, "h"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(18, 19, "i"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(19, 20, "j"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(20, 21, "k"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(21, 22, "l"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(22, 23, "m"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(23, 24, "n"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(24, 25, "o"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(25, 26, "p"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(26, 27, "q"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(27, 28, "r"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(28, 29, "s"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(29, 30, "t"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(30, 31, "u"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(31, 32, "v"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(32, 33, "w"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(33, 34, "x"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(34, 35, "y"));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerToCharsTest(35, 36, "z"));

	// 出力文字列が[first, last)に収まらない場合のテスト
	// 変換に失敗した場合の[first, last)の状態は未規定。
	{
		char buf[4];
		auto ret = hamon::to_chars(buf, buf+sizeof(buf), 12345);
		EXPECT_EQ(ret.ptr, buf+sizeof(buf));
		EXPECT_EQ(ret.ec, hamon::errc::value_too_large);
	}
	{
		char buf[5];
		auto ret = hamon::to_chars(buf, buf+sizeof(buf), 12345);
		EXPECT_EQ(hamon::string_view(buf, ret.ptr), "12345");
		EXPECT_EQ(ret.ec, hamon::errc{});
	}
	{
		char buf[7];
		auto ret = hamon::to_chars(buf, buf+sizeof(buf), 0xFFFFFFFF, 16);
		EXPECT_EQ(ret.ptr, buf+sizeof(buf));
		EXPECT_EQ(ret.ec, hamon::errc::value_too_large);
	}
	{
		char buf[8];
		auto ret = hamon::to_chars(buf, buf+sizeof(buf), 0xFFFFFFFF, 16);
		EXPECT_EQ(hamon::string_view(buf, ret.ptr), "ffffffff");
		EXPECT_EQ(ret.ec, hamon::errc{});
	}
}

#undef VERIFY

}	// namespace to_chars_test

}	// namespace hamon_charconv_test
