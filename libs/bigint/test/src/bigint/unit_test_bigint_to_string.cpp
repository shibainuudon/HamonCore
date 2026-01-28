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
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(ToStringSignedTest<hamon::bigint>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(ToStringSignedTest<hamon::inplace_bigint<128>>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(ToStringSignedTest<hamon::inplace_bigint<256>>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(ToStringSignedTest<hamon::inplace_bigint<512>>());

	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(ToStringSignedTest<hamon::int32_t>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(ToStringSignedTest<hamon::int64_t>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(ToStringSignedTest<hamon::int128_t>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(ToStringSignedTest<hamon::int256_t>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(ToStringSignedTest<hamon::int512_t>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(ToStringSignedTest<hamon::int1024_t>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(ToStringSignedTest<hamon::int2048_t>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(ToStringUnsignedTest<hamon::uint32_t>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(ToStringUnsignedTest<hamon::uint64_t>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(ToStringUnsignedTest<hamon::uint128_t>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(ToStringUnsignedTest<hamon::uint256_t>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(ToStringUnsignedTest<hamon::uint512_t>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(ToStringUnsignedTest<hamon::uint1024_t>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(ToStringUnsignedTest<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_to_string_test

}	// namespace hamon_bigint_test
