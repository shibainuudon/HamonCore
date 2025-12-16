/**
 *	@file	unit_test_charconv_from_chars.cpp
 *
 *	@brief	from_chars のテスト
 */

#include <hamon/charconv/from_chars.hpp>
#include <hamon/string_view.hpp>
#include <hamon/system_error/errc.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_charconv_test
{

namespace from_chars_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
IntegerFromCharsTest(hamon::string_view sv, int base, T expected, hamon::size_t length, hamon::errc ec = {})
{
	T value{};
	auto ret = hamon::from_chars(sv.data(), sv.data() + sv.size(), value, base);
	VERIFY(value == expected);
	VERIFY(ret.ptr == sv.data() + length);
	VERIFY(ret.ec == ec);

	return true;
}

GTEST_TEST(CharConvTest, FromCharsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("12345", 10, 12345, 5));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("-12345", 10, -12345, 6));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("123 45", 10, 123, 3));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("00000123456789 is decimal", 10, 123456789, 14));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("0000", 10, 0, 4));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("0 1 2 3", 10, 0, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("00ab", 10, 0, 2));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("11111111", 10, 11111111, 8));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("11111111", 2, 255, 8));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("01010011", 2, 83, 8));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("777", 8, 511, 3));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("ffff", 16, 65535, 4));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("FFFF", 16, 65535, 4));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("abcdefghijk", 16, 11259375, 6));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("ABCDEFGHIJK", 16, 11259375, 6));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("aBcdEFGhiJK", 16, 11259375, 6));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest<hamon::int8_t>("127", 10, 127, 3));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest<hamon::int8_t>("-128", 10, -128, 4));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest<hamon::uint8_t>("255", 10, 255, 3));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest<hamon::int16_t>("32767", 10, 32767, 5));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest<hamon::int16_t>("-32768", 10, -32768, 6));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest<hamon::uint16_t>("65535", 10, 65535, 5));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("a", 11, 10, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("b", 12, 11, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("c", 13, 12, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("d", 14, 13, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("e", 15, 14, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("f", 16, 15, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("g", 17, 16, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("h", 18, 17, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("i", 19, 18, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("j", 20, 19, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("k", 21, 20, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("l", 22, 21, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("m", 23, 22, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("n", 24, 23, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("o", 25, 24, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("p", 26, 25, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("q", 27, 26, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("r", 28, 27, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("s", 29, 28, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("t", 30, 29, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("u", 31, 30, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("v", 32, 31, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("w", 33, 32, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("x", 34, 33, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("y", 35, 34, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("z", 36, 35, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("A", 11, 10, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("B", 12, 11, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("C", 13, 12, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("D", 14, 13, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("E", 15, 14, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("F", 16, 15, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("G", 17, 16, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("H", 18, 17, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("I", 19, 18, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("J", 20, 19, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("K", 21, 20, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("L", 22, 21, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("M", 23, 22, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("N", 24, 23, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("O", 25, 24, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("P", 26, 25, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("Q", 27, 26, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("R", 28, 27, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("S", 29, 28, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("T", 30, 29, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("U", 31, 30, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("V", 32, 31, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("W", 33, 32, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("X", 34, 33, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("Y", 35, 34, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("Z", 36, 35, 1));

	// 0xで始まっても考慮されない('x'の部分でマッチング終了)
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("0xffff", 16, 0, 1));

	// パターンにマッチする文字列が見つからない場合
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("a123", 10, 0, 0, hamon::errc::invalid_argument));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("+10", 10, 0, 0, hamon::errc::invalid_argument));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest(" 1", 10, 0, 0, hamon::errc::invalid_argument));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("", 10, 0, 0, hamon::errc::invalid_argument));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest("ffff", 15, 0, 0, hamon::errc::invalid_argument));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest<hamon::uint8_t>("-1", 10, 0, 0, hamon::errc::invalid_argument));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest<hamon::uint8_t>("+1", 10, 0, 0, hamon::errc::invalid_argument));

	// 変換した結果の値がvalueの型では表現できない場合
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest<hamon::int8_t>("128", 10, 0, 3, hamon::errc::result_out_of_range));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest<hamon::int8_t>("-129", 10, 0, 4, hamon::errc::result_out_of_range));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest<hamon::uint8_t>("256", 10, 0, 3, hamon::errc::result_out_of_range));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest<hamon::int16_t>("32768", 10, 0, 5, hamon::errc::result_out_of_range));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest<hamon::int16_t>("-32769", 10, 0, 6, hamon::errc::result_out_of_range));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest<hamon::uint16_t>("65536", 10, 0, 5, hamon::errc::result_out_of_range));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest<signed   int>("ffffffffffffffffffffffffffffffff", 16, 0, 32, hamon::errc::result_out_of_range));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IntegerFromCharsTest<unsigned int>("ffffffffffffffffffffffffffffffff", 16, 0, 32, hamon::errc::result_out_of_range));
}

#undef VERIFY

}	// namespace from_chars_test

}	// namespace hamon_charconv_test
