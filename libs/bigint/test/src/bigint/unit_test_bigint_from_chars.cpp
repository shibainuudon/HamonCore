/**
 *	@file	unit_test_bigint_from_chars.cpp
 *
 *	@brief	from_chars関数のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/system_error/errc.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

//#include <chrono>

namespace hamon_bigint_test
{

namespace bigint_from_chars_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
test_impl(hamon::string_view sv, int base, BigInt const& expected, hamon::size_t length, hamon::errc ec = {})
{
	BigInt value{};
	auto ret = hamon::from_chars(sv.data(), sv.data() + sv.size(), value, base);
	VERIFY(value == expected);
	VERIFY(ret.ptr == sv.data() + length);
	VERIFY(ret.ec == ec);
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
test1()
{
	VERIFY(test_impl("0", 10, BigInt{0}, 1));
	VERIFY(test_impl("12345", 10, BigInt{12345}, 5));
	VERIFY(test_impl("-12345", 10, BigInt{-12345}, 6));
	VERIFY(test_impl("0123456789abcdef", 10, BigInt{123456789}, 10));
	VERIFY(test_impl("0123456789abcdef", 16, BigInt{0x123456789abcdef}, 16));
	VERIFY(test_impl("11111111", 10, BigInt{11111111}, 8));
	VERIFY(test_impl("11111111", 2, BigInt{255}, 8));
	VERIFY(test_impl("-11111111", 10, BigInt{-11111111}, 9));
	VERIFY(test_impl("-11111111", 2, BigInt{-255}, 9));
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
test2()
{
	VERIFY(test_impl("1",  2, BigInt{ 1}, 1));
	VERIFY(test_impl("2",  3, BigInt{ 2}, 1));
	VERIFY(test_impl("3",  4, BigInt{ 3}, 1));
	VERIFY(test_impl("4",  5, BigInt{ 4}, 1));
	VERIFY(test_impl("5",  6, BigInt{ 5}, 1));
	VERIFY(test_impl("6",  7, BigInt{ 6}, 1));
	VERIFY(test_impl("7",  8, BigInt{ 7}, 1));
	VERIFY(test_impl("8",  9, BigInt{ 8}, 1));
	VERIFY(test_impl("9", 10, BigInt{ 9}, 1));
	VERIFY(test_impl("a", 11, BigInt{10}, 1));
	VERIFY(test_impl("b", 12, BigInt{11}, 1));
	VERIFY(test_impl("c", 13, BigInt{12}, 1));
	VERIFY(test_impl("d", 14, BigInt{13}, 1));
	VERIFY(test_impl("e", 15, BigInt{14}, 1));
	VERIFY(test_impl("f", 16, BigInt{15}, 1));
	VERIFY(test_impl("g", 17, BigInt{16}, 1));
	VERIFY(test_impl("h", 18, BigInt{17}, 1));
	VERIFY(test_impl("i", 19, BigInt{18}, 1));
	VERIFY(test_impl("j", 20, BigInt{19}, 1));
	VERIFY(test_impl("k", 21, BigInt{20}, 1));
	VERIFY(test_impl("l", 22, BigInt{21}, 1));
	VERIFY(test_impl("m", 23, BigInt{22}, 1));
	VERIFY(test_impl("n", 24, BigInt{23}, 1));
	VERIFY(test_impl("o", 25, BigInt{24}, 1));
	VERIFY(test_impl("p", 26, BigInt{25}, 1));
	VERIFY(test_impl("q", 27, BigInt{26}, 1));
	VERIFY(test_impl("r", 28, BigInt{27}, 1));
	VERIFY(test_impl("s", 29, BigInt{28}, 1));
	VERIFY(test_impl("t", 30, BigInt{29}, 1));
	VERIFY(test_impl("u", 31, BigInt{30}, 1));
	VERIFY(test_impl("v", 32, BigInt{31}, 1));
	VERIFY(test_impl("w", 33, BigInt{32}, 1));
	VERIFY(test_impl("x", 34, BigInt{33}, 1));
	VERIFY(test_impl("y", 35, BigInt{34}, 1));
	VERIFY(test_impl("z", 36, BigInt{35}, 1));
	VERIFY(test_impl("A", 11, BigInt{10}, 1));
	VERIFY(test_impl("B", 12, BigInt{11}, 1));
	VERIFY(test_impl("C", 13, BigInt{12}, 1));
	VERIFY(test_impl("D", 14, BigInt{13}, 1));
	VERIFY(test_impl("E", 15, BigInt{14}, 1));
	VERIFY(test_impl("F", 16, BigInt{15}, 1));
	VERIFY(test_impl("G", 17, BigInt{16}, 1));
	VERIFY(test_impl("H", 18, BigInt{17}, 1));
	VERIFY(test_impl("I", 19, BigInt{18}, 1));
	VERIFY(test_impl("J", 20, BigInt{19}, 1));
	VERIFY(test_impl("K", 21, BigInt{20}, 1));
	VERIFY(test_impl("L", 22, BigInt{21}, 1));
	VERIFY(test_impl("M", 23, BigInt{22}, 1));
	VERIFY(test_impl("N", 24, BigInt{23}, 1));
	VERIFY(test_impl("O", 25, BigInt{24}, 1));
	VERIFY(test_impl("P", 26, BigInt{25}, 1));
	VERIFY(test_impl("Q", 27, BigInt{26}, 1));
	VERIFY(test_impl("R", 28, BigInt{27}, 1));
	VERIFY(test_impl("S", 29, BigInt{28}, 1));
	VERIFY(test_impl("T", 30, BigInt{29}, 1));
	VERIFY(test_impl("U", 31, BigInt{30}, 1));
	VERIFY(test_impl("V", 32, BigInt{31}, 1));
	VERIFY(test_impl("W", 33, BigInt{32}, 1));
	VERIFY(test_impl("X", 34, BigInt{33}, 1));
	VERIFY(test_impl("Y", 35, BigInt{34}, 1));
	VERIFY(test_impl("Z", 36, BigInt{35}, 1));
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntTest, FromCharsTest)
{
#if 0
	{
		auto t0 = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < 100000; ++i)
		{
			const char* s =
				"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
				"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
				"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
				"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
				"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
				"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
				"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
				"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
			hamon::inplace_bigint<4000> bi;
			auto ret = hamon::from_chars(s, s + std::strlen(s), bi, 10);
			EXPECT_TRUE(ret.ec == hamon::errc{});
		}

		auto t1 = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
		std::cout << elapsed.count() << " ms" << std::endl;
	}
	// 最適化前
	// Debug:   1539 ms
	// Release:  117 ms

	// bigint_algo::multiplyでの不要なzeroを削除
	// Debug:   1223 ms
	// Release:   94 ms

	// bigint_algo::addでの不要なzeroを削除
	// Debug:    811 ms
	// Release:   93 ms

	// bigint_algo::multiplyをin-placeに
	// Debug:    715 ms
	// Release:   86 ms

	// bigint_algo::multiply_addを追加
	// Debug:    543 ms
	// Release:   81 ms

	// テスト文字列の長さを 1200 -> 800 に、繰り返し回数を 10000 -> 100000 に変更
	// (実際に使用するケースにより近づける意図)
	// Debug:    3230 ms
	// Release:   555 ms

	// bigint_algo::multiply_addを最適化
	// Debug:    2892 ms
	// Release:   532 ms

	// 不要なlog2の呼び出しを回避
	// Debug:    2402 ms
	// Release:   320 ms
#endif

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1<hamon::inplace_bigint<128>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1<hamon::inplace_bigint<256>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1<hamon::inplace_bigint<512>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test1<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test1<hamon::int2048_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test1<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test1<hamon::uint2048_t>());

	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<hamon::inplace_bigint<128>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<hamon::inplace_bigint<256>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<hamon::inplace_bigint<512>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test2<hamon::int2048_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test2<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test2<hamon::uint2048_t>());
}

}	// namespace bigint_from_chars_test

}	// namespace hamon_bigint_test
