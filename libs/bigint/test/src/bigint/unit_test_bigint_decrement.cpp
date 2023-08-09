/**
 *	@file	unit_test_bigint_decrement.cpp
 *
 *	@brief	operator--のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_decrement_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
DecrementTest()
{
	{
		auto x1 = BigInt(2);
		VERIFY(x1 == BigInt( 2));

		auto x2 = --x1;
		VERIFY(x1 == BigInt( 1));
		VERIFY(x2 == BigInt( 1));

		auto x3 = --x1;
		VERIFY(x1 == BigInt( 0));
		VERIFY(x3 == BigInt( 0));

		auto x4 = --x1;
		VERIFY(x1 == BigInt(-1));
		VERIFY(x4 == BigInt(-1));

		auto x5 = --x1;
		VERIFY(x1 == BigInt(-2));
		VERIFY(x5 == BigInt(-2));
	}
	{
		auto x1 = BigInt(2);
		VERIFY(x1 == BigInt( 2));

		auto x2 = x1--;
		VERIFY(x1 == BigInt( 1));
		VERIFY(x2 == BigInt( 2));

		auto x3 = x1--;
		VERIFY(x1 == BigInt( 0));
		VERIFY(x3 == BigInt( 1));

		auto x4 = x1--;
		VERIFY(x1 == BigInt(-1));
		VERIFY(x4 == BigInt( 0));

		auto x5 = x1--;
		VERIFY(x1 == BigInt(-2));
		VERIFY(x5 == BigInt(-1));
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
DecrementTest2()
{
	{
		BigInt x1{"1000000000000000000000"};

		auto x2 = --x1;
		VERIFY(x1 == BigInt{"999999999999999999999"});
		VERIFY(x2 == BigInt{"999999999999999999999"});

		auto x3 = --x1;
		VERIFY(x1 == BigInt{"999999999999999999998"});
		VERIFY(x3 == BigInt{"999999999999999999998"});
	}
	{
		BigInt x1{"1000000000000000000000"};

		auto x2 = x1--;
		VERIFY(x1 == BigInt{"999999999999999999999"});
		VERIFY(x2 == BigInt{"1000000000000000000000"});

		auto x3 = x1--;
		VERIFY(x1 == BigInt{"999999999999999999998"});
		VERIFY(x3 == BigInt{"999999999999999999999"});
	}
	return true;
}

GTEST_TEST(BigIntTest, DecrementTest)
{
	EXPECT_TRUE(DecrementTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest<hamon::uint2048_t>());

	EXPECT_TRUE(DecrementTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest2<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest2<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest2<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest2<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecrementTest2<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_decrement_test

}	// namespace hamon_bigint_test
