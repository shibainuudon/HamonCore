/**
 *	@file	unit_test_bigint_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_ctor_default_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
CtorDefaultTest()
{
	{
		BigInt x{};
		VERIFY(x == BigInt(0));
	}
	{
		BigInt x = {};
		VERIFY(x == BigInt(0));
	}
	return true;
}

GTEST_TEST(BigIntTest, CtorDefaultTest)
{
	EXPECT_TRUE(CtorDefaultTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_ctor_default_test

}	// namespace hamon_bigint_test
