/**
 *	@file	unit_test_bigint_unary_plus.cpp
 *
 *	@brief	operator+ のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_unary_plus_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
UnaryPlusTest()
{
	{
		auto x = BigInt(0);
		VERIFY(+x == BigInt( 0));
	}
	{
		auto x = BigInt(1);
		VERIFY(+x == BigInt(1));
	}
	{
		auto x = BigInt(2);
		VERIFY(+x == BigInt(2));
	}
	{
		auto x = BigInt(-1);
		VERIFY(+x == BigInt(-1));
	}
	{
		auto x = BigInt(-2);
		VERIFY(+x == BigInt(-2));
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
UnaryPlusTest2()
{
	{
		auto x = BigInt{"12345678901234567890"};
		VERIFY(+x == BigInt{"12345678901234567890"});
	}
	{
		auto x = BigInt{"-12345678901234567890"};
		VERIFY(+x == BigInt{"-12345678901234567890"});
	}
	return true;
}

GTEST_TEST(BigIntTest, UnaryPlusTest)
{
	EXPECT_TRUE(UnaryPlusTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusTest<hamon::uint2048_t>());

	EXPECT_TRUE(UnaryPlusTest2<hamon::bigint>());

	EXPECT_TRUE(UnaryPlusTest2<hamon::int128_t>());
	EXPECT_TRUE(UnaryPlusTest2<hamon::int256_t>());
	EXPECT_TRUE(UnaryPlusTest2<hamon::int512_t>());
	EXPECT_TRUE(UnaryPlusTest2<hamon::int1024_t>());
	EXPECT_TRUE(UnaryPlusTest2<hamon::int2048_t>());

	EXPECT_TRUE(UnaryPlusTest2<hamon::uint128_t>());
	EXPECT_TRUE(UnaryPlusTest2<hamon::uint256_t>());
	EXPECT_TRUE(UnaryPlusTest2<hamon::uint512_t>());
	EXPECT_TRUE(UnaryPlusTest2<hamon::uint1024_t>());
	EXPECT_TRUE(UnaryPlusTest2<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_unary_plus_test

}	// namespace hamon_bigint_test
