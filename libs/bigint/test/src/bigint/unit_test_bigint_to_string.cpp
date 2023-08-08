/**
 *	@file	unit_test_bigint_to_string.cpp
 *
 *	@brief	to_string関数のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_to_string_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
ToStringTestImpl(BigInt const& value, const char* expected)
{
	auto ret = hamon::to_string(value);
	VERIFY(ret == expected);
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
ToStringSignedTest()
{
	VERIFY(ToStringTestImpl(BigInt{ 0}, "0"));
	VERIFY(ToStringTestImpl(BigInt{ 1}, "1"));
	VERIFY(ToStringTestImpl(BigInt{-1}, "-1"));
	VERIFY(ToStringTestImpl(BigInt{ 2}, "2"));
	VERIFY(ToStringTestImpl(BigInt{-2}, "-2"));
	VERIFY(ToStringTestImpl(BigInt{12345}, "12345"));
	VERIFY(ToStringTestImpl(BigInt{-123456}, "-123456"));
	VERIFY(ToStringTestImpl(BigInt{0xFFFF}, "65535"));
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
ToStringUnsignedTest()
{
	VERIFY(ToStringTestImpl(BigInt{ 0}, "0"));
	VERIFY(ToStringTestImpl(BigInt{ 1}, "1"));
	VERIFY(ToStringTestImpl(BigInt{ 2}, "2"));
	VERIFY(ToStringTestImpl(BigInt{12345}, "12345"));
	VERIFY(ToStringTestImpl(BigInt{0xFFFF}, "65535"));
	return true;
}

GTEST_TEST(BigIntTest, ToStringTest)
{
	EXPECT_TRUE(ToStringSignedTest<hamon::bigint>());
	EXPECT_TRUE(ToStringSignedTest<hamon::int32_t>());
	EXPECT_TRUE(ToStringSignedTest<hamon::int64_t>());
	EXPECT_TRUE(ToStringSignedTest<hamon::int128_t>());
	EXPECT_TRUE(ToStringSignedTest<hamon::int256_t>());
	EXPECT_TRUE(ToStringSignedTest<hamon::int512_t>());
	EXPECT_TRUE(ToStringSignedTest<hamon::int1024_t>());
	EXPECT_TRUE(ToStringSignedTest<hamon::int2048_t>());
	EXPECT_TRUE(ToStringUnsignedTest<hamon::uint32_t>());
	EXPECT_TRUE(ToStringUnsignedTest<hamon::uint64_t>());
	EXPECT_TRUE(ToStringUnsignedTest<hamon::uint128_t>());
	EXPECT_TRUE(ToStringUnsignedTest<hamon::uint256_t>());
	EXPECT_TRUE(ToStringUnsignedTest<hamon::uint512_t>());
	EXPECT_TRUE(ToStringUnsignedTest<hamon::uint1024_t>());
	EXPECT_TRUE(ToStringUnsignedTest<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_to_string_test

}	// namespace hamon_bigint_test
