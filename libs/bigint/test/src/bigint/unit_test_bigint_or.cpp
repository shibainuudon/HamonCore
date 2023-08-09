/**
 *	@file	unit_test_bigint_or.cpp
 *
 *	@brief	operator|のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_or_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
OrTest()
{
	{
		auto x = BigInt{0x0F} | BigInt{0x35};
		VERIFY(x == 0x3F);
	}
	{
		auto x = BigInt{0x35} | BigInt{0xf0};
		VERIFY(x == 0xF5);
	}
	{
		auto x = BigInt{0x0F} | BigInt{0x12};
		VERIFY(x == 0x1F);
	}
	{
		auto x = BigInt{0x77} | BigInt{0x20};
		VERIFY(x == 0x77);
	}
	{
		auto x = BigInt{0x123456} | BigInt{0xf00000};
		VERIFY(x == 0xF23456);
	}
	{
		auto x = BigInt{0x123456} | BigInt{0x0f0000};
		VERIFY(x == 0x1F3456);
	}
	{
		auto x = BigInt{0x123456} | BigInt{0x00000f};
		VERIFY(x == 0x12345F);
	}
	{
		auto x = BigInt{0x123456} | BigInt{0xf0f0f0};
		VERIFY(x == 0xF2F4F6);
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
OrTest2()
{
	{
		auto x =
			BigInt{0x01} |
			BigInt{"0x8000000000000000000000000000000"};
		VERIFY(x == BigInt{"0x8000000000000000000000000000001"});
	}
	{
		auto x =
			BigInt{"0xF0FF00FFF000FFFF0000FFFFF00000FFF"} |
			BigInt{"0x1234567890ABCDEF0123456789ABCDEF0"};
		VERIFY(x == BigInt{"0xF2FF56FFF0ABFFFF0123FFFFF9ABCDFFF"});
	}
	{
		auto x =
			BigInt{"0x1234000000000000000000000000000"} | 
			BigInt{0x123};
		VERIFY(x == BigInt{"0x1234000000000000000000000000123"});
	}
	return true;
}

GTEST_TEST(BigIntTest, OrTest)
{
	EXPECT_TRUE(OrTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::uint2048_t>());

	EXPECT_TRUE(OrTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest2<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest2<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest2<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest2<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest2<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_or_test

}	// namespace hamon_bigint_test
