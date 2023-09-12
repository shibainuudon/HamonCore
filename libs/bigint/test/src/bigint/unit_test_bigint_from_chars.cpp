/**
 *	@file	unit_test_bigint_from_chars.cpp
 *
 *	@brief	from_chars関数のテスト
 */

#include <hamon/bigint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_from_chars_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
FromCharsTestImpl(hamon::string_view sv, int base, BigInt const& expected, hamon::size_t length, std::errc ec = {})
{
	BigInt value{};
	auto ret = hamon::from_chars(sv.begin(), sv.end(), value, base);
	VERIFY(value == expected);
	VERIFY(ret.ptr == sv.begin() + length);
	VERIFY(ret.ec == ec);
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
FromCharsTest()
{
	VERIFY(FromCharsTestImpl("0", 10, BigInt{0}, 1));
	VERIFY(FromCharsTestImpl("12345", 10, BigInt{12345}, 5));
	VERIFY(FromCharsTestImpl("-12345", 10, BigInt{-12345}, 6));
	VERIFY(FromCharsTestImpl("0123456789abcdef", 10, BigInt{123456789}, 10));
	VERIFY(FromCharsTestImpl("0123456789abcdef", 16, BigInt{0x123456789abcdef}, 16));
	VERIFY(FromCharsTestImpl("11111111", 10, BigInt{11111111}, 8));
	VERIFY(FromCharsTestImpl("11111111", 2, BigInt{255}, 8));
	VERIFY(FromCharsTestImpl("-11111111", 10, BigInt{-11111111}, 9));
	VERIFY(FromCharsTestImpl("-11111111", 2, BigInt{-255}, 9));
	VERIFY(FromCharsTestImpl("1",  2, BigInt{ 1}, 1));
	VERIFY(FromCharsTestImpl("2",  3, BigInt{ 2}, 1));
	VERIFY(FromCharsTestImpl("3",  4, BigInt{ 3}, 1));
	VERIFY(FromCharsTestImpl("4",  5, BigInt{ 4}, 1));
	VERIFY(FromCharsTestImpl("5",  6, BigInt{ 5}, 1));
	VERIFY(FromCharsTestImpl("6",  7, BigInt{ 6}, 1));
	VERIFY(FromCharsTestImpl("7",  8, BigInt{ 7}, 1));
	VERIFY(FromCharsTestImpl("8",  9, BigInt{ 8}, 1));
	VERIFY(FromCharsTestImpl("9", 10, BigInt{ 9}, 1));
	VERIFY(FromCharsTestImpl("a", 11, BigInt{10}, 1));
	VERIFY(FromCharsTestImpl("b", 12, BigInt{11}, 1));
	VERIFY(FromCharsTestImpl("c", 13, BigInt{12}, 1));
	VERIFY(FromCharsTestImpl("d", 14, BigInt{13}, 1));
	VERIFY(FromCharsTestImpl("e", 15, BigInt{14}, 1));
	VERIFY(FromCharsTestImpl("f", 16, BigInt{15}, 1));
	VERIFY(FromCharsTestImpl("g", 17, BigInt{16}, 1));
	VERIFY(FromCharsTestImpl("h", 18, BigInt{17}, 1));
	VERIFY(FromCharsTestImpl("i", 19, BigInt{18}, 1));
	VERIFY(FromCharsTestImpl("j", 20, BigInt{19}, 1));
	VERIFY(FromCharsTestImpl("k", 21, BigInt{20}, 1));
	VERIFY(FromCharsTestImpl("l", 22, BigInt{21}, 1));
	VERIFY(FromCharsTestImpl("m", 23, BigInt{22}, 1));
	VERIFY(FromCharsTestImpl("n", 24, BigInt{23}, 1));
	VERIFY(FromCharsTestImpl("o", 25, BigInt{24}, 1));
	VERIFY(FromCharsTestImpl("p", 26, BigInt{25}, 1));
	VERIFY(FromCharsTestImpl("q", 27, BigInt{26}, 1));
	VERIFY(FromCharsTestImpl("r", 28, BigInt{27}, 1));
	VERIFY(FromCharsTestImpl("s", 29, BigInt{28}, 1));
	VERIFY(FromCharsTestImpl("t", 30, BigInt{29}, 1));
	VERIFY(FromCharsTestImpl("u", 31, BigInt{30}, 1));
	VERIFY(FromCharsTestImpl("v", 32, BigInt{31}, 1));
	VERIFY(FromCharsTestImpl("w", 33, BigInt{32}, 1));
	VERIFY(FromCharsTestImpl("x", 34, BigInt{33}, 1));
	VERIFY(FromCharsTestImpl("y", 35, BigInt{34}, 1));
	VERIFY(FromCharsTestImpl("z", 36, BigInt{35}, 1));
	VERIFY(FromCharsTestImpl("A", 11, BigInt{10}, 1));
	VERIFY(FromCharsTestImpl("B", 12, BigInt{11}, 1));
	VERIFY(FromCharsTestImpl("C", 13, BigInt{12}, 1));
	VERIFY(FromCharsTestImpl("D", 14, BigInt{13}, 1));
	VERIFY(FromCharsTestImpl("E", 15, BigInt{14}, 1));
	VERIFY(FromCharsTestImpl("F", 16, BigInt{15}, 1));
	VERIFY(FromCharsTestImpl("G", 17, BigInt{16}, 1));
	VERIFY(FromCharsTestImpl("H", 18, BigInt{17}, 1));
	VERIFY(FromCharsTestImpl("I", 19, BigInt{18}, 1));
	VERIFY(FromCharsTestImpl("J", 20, BigInt{19}, 1));
	VERIFY(FromCharsTestImpl("K", 21, BigInt{20}, 1));
	VERIFY(FromCharsTestImpl("L", 22, BigInt{21}, 1));
	VERIFY(FromCharsTestImpl("M", 23, BigInt{22}, 1));
	VERIFY(FromCharsTestImpl("N", 24, BigInt{23}, 1));
	VERIFY(FromCharsTestImpl("O", 25, BigInt{24}, 1));
	VERIFY(FromCharsTestImpl("P", 26, BigInt{25}, 1));
	VERIFY(FromCharsTestImpl("Q", 27, BigInt{26}, 1));
	VERIFY(FromCharsTestImpl("R", 28, BigInt{27}, 1));
	VERIFY(FromCharsTestImpl("S", 29, BigInt{28}, 1));
	VERIFY(FromCharsTestImpl("T", 30, BigInt{29}, 1));
	VERIFY(FromCharsTestImpl("U", 31, BigInt{30}, 1));
	VERIFY(FromCharsTestImpl("V", 32, BigInt{31}, 1));
	VERIFY(FromCharsTestImpl("W", 33, BigInt{32}, 1));
	VERIFY(FromCharsTestImpl("X", 34, BigInt{33}, 1));
	VERIFY(FromCharsTestImpl("Y", 35, BigInt{34}, 1));
	VERIFY(FromCharsTestImpl("Z", 36, BigInt{35}, 1));
	return true;
}

GTEST_TEST(BigIntTest, FromCharsTest)
{
	EXPECT_TRUE(FromCharsTest<hamon::bigint>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest<hamon::int2048_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_from_chars_test

}	// namespace hamon_bigint_test
