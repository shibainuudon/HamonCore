/**
 *	@file	unit_test_bigint_to_chars.cpp
 *
 *	@brief	to_chars関数のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/string_view.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_to_chars_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
ToCharsTestImpl(BigInt const& value, int base, const char* expected)
{
	char buf[1024]{};
	auto ret = hamon::to_chars(buf, buf+sizeof(buf), value, base);
	VERIFY(hamon::string_view(buf, ret.ptr) == expected);
	VERIFY(ret.ec == std::errc{});
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
ToCharsSignedTest()
{
	VERIFY(ToCharsTestImpl(BigInt{ 0}, 10, "0"));
	VERIFY(ToCharsTestImpl(BigInt{ 1}, 10, "1"));
	VERIFY(ToCharsTestImpl(BigInt{-1}, 10, "-1"));
	VERIFY(ToCharsTestImpl(BigInt{ 2}, 10, "2"));
	VERIFY(ToCharsTestImpl(BigInt{-2}, 10, "-2"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 10, "12345"));
	VERIFY(ToCharsTestImpl(BigInt{-123456}, 10, "-123456"));
	VERIFY(ToCharsTestImpl(BigInt{0xFFFF}, 10, "65535"));

	VERIFY(ToCharsTestImpl(BigInt{12345}, 16, "3039"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 16, "-3039"));
	VERIFY(ToCharsTestImpl(BigInt{0xFFFF}, 16, "ffff"));
	VERIFY(ToCharsTestImpl(BigInt{-0xFFFF}, 16, "-ffff"));

	VERIFY(ToCharsTestImpl(BigInt{-12345}, 2, "-11000000111001"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 3, "-121221020"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 4, "-3000321"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 5, "-343340"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 6, "-133053"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 7, "-50664"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 8, "-30071"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 9, "-17836"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 10, "-12345"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 11, "-9303"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 12, "-7189"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 13, "-5808"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 14, "-46db"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 15, "-39d0"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 16, "-3039"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 17, "-28c3"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 18, "-221f"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 19, "-1f3e"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 20, "-1ah5"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 21, "-16ki"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 22, "-13b3"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 23, "-107h"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 24, "-la9"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 25, "-jik"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 26, "-i6l"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 27, "-gp6"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 28, "-fkp"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 29, "-ejk"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 30, "-dlf"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 31, "-cq7"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 32, "-c1p"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 33, "-bb3"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 34, "-an3"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 35, "-a2p"));
	VERIFY(ToCharsTestImpl(BigInt{-12345}, 36, "-9ix"));
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
ToCharsUnsignedTest()
{
	VERIFY(ToCharsTestImpl(BigInt{ 0}, 10, "0"));
	VERIFY(ToCharsTestImpl(BigInt{ 1}, 10, "1"));
	VERIFY(ToCharsTestImpl(BigInt{ 2}, 10, "2"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 10, "12345"));
	VERIFY(ToCharsTestImpl(BigInt{0xFFFF}, 10, "65535"));

	VERIFY(ToCharsTestImpl(BigInt{12345}, 16, "3039"));
	VERIFY(ToCharsTestImpl(BigInt{0xFFFF}, 16, "ffff"));

	VERIFY(ToCharsTestImpl(BigInt{12345}, 2, "11000000111001"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 3, "121221020"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 4, "3000321"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 5, "343340"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 6, "133053"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 7, "50664"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 8, "30071"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 9, "17836"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 10, "12345"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 11, "9303"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 12, "7189"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 13, "5808"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 14, "46db"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 15, "39d0"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 16, "3039"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 17, "28c3"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 18, "221f"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 19, "1f3e"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 20, "1ah5"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 21, "16ki"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 22, "13b3"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 23, "107h"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 24, "la9"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 25, "jik"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 26, "i6l"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 27, "gp6"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 28, "fkp"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 29, "ejk"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 30, "dlf"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 31, "cq7"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 32, "c1p"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 33, "bb3"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 34, "an3"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 35, "a2p"));
	VERIFY(ToCharsTestImpl(BigInt{12345}, 36, "9ix"));
	return true;
}

GTEST_TEST(BigIntTest, ToCharsTest)
{
	EXPECT_TRUE(ToCharsSignedTest<hamon::bigint>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToCharsSignedTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToCharsSignedTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToCharsSignedTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToCharsSignedTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToCharsSignedTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ToCharsSignedTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ToCharsSignedTest<hamon::int2048_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToCharsUnsignedTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToCharsUnsignedTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToCharsUnsignedTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToCharsUnsignedTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToCharsUnsignedTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ToCharsUnsignedTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ToCharsUnsignedTest<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_to_chars_test

}	// namespace hamon_bigint_test
