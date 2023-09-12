/**
 *	@file	unit_test_bigint_unary_minus.cpp
 *
 *	@brief	operator- のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4146)	// 符号付きの値を代入する変数は、符号付き型にキャストしなければなりません。

namespace hamon_bigint_test
{

namespace bigint_unary_minus_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
UnaryMinusTest()
{
	{
		auto x = BigInt(0);
		VERIFY(-x == BigInt( 0));
	}
	{
		auto x = BigInt(1);
		VERIFY(-x == BigInt(-1));
	}
	{
		auto x = BigInt(2);
		VERIFY(-x == BigInt(-2));
	}
	{
		auto x = BigInt(-1);
		VERIFY(-x == BigInt( 1));
	}
	{
		auto x = BigInt(-2);
		VERIFY(-x == BigInt( 2));
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
UnaryMinusTest2()
{
	{
		auto x = BigInt{"12345678901234567890"};
		VERIFY(-x == BigInt{"-12345678901234567890"});
	}
	{
		auto x = BigInt{"-12345678901234567890"};
		VERIFY(-x == BigInt{"12345678901234567890"});
	}
	return true;
}

GTEST_TEST(BigIntTest, UnaryMinusTest)
{
	EXPECT_TRUE(UnaryMinusTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnaryMinusTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnaryMinusTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnaryMinusTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnaryMinusTest<hamon::uint2048_t>());

	EXPECT_TRUE(UnaryMinusTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest2<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnaryMinusTest2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnaryMinusTest2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryMinusTest2<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnaryMinusTest2<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnaryMinusTest2<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_unary_minus_test

}	// namespace hamon_bigint_test

HAMON_WARNING_POP()
