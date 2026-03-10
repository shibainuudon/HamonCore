/**
 *	@file	unit_test_bigint_assign_copy.cpp
 *
 *	@brief	コピー代入演算子のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_assign_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
test()
{
	{
		BigInt const x{123};
		BigInt y;
		VERIFY(y == 0);
		y = x;
		VERIFY(y != 0);
		VERIFY(y == 123);
	}
	{
		BigInt const x{"1000000000000000000000"};
		BigInt y{42};
		VERIFY(y == 42);
		y = x;
		VERIFY(y != 42);
		VERIFY(y == x);
		y = BigInt{13};
		VERIFY(y != x);
		VERIFY(y == 13);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntTest, AssignCopyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<hamon::inplace_bigint<128>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<hamon::inplace_bigint<2048>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<hamon::inplace_bigint<4096>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test<hamon::uint2048_t>());
}

}	// namespace bigint_assign_copy_test

}	// namespace hamon_bigint_test
