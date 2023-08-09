/**
 *	@file	unit_test_bigint_mul_equal.cpp
 *
 *	@brief	operator*=のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_mul_equal_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
MulEqualTest()
{
	{
		BigInt x{1};
		VERIFY(x == BigInt(1));

		x *= BigInt{2};
		VERIFY(x == BigInt(2));

		x *= BigInt{2};
		VERIFY(x == BigInt(4));

		x *= BigInt{12345};
		VERIFY(x == BigInt(49380));

		x *= BigInt(-1);
		VERIFY(x == BigInt(-49380));

		x *= 0;
		VERIFY(x == BigInt(0));
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
MulEqualTest2()
{
	{
		BigInt x{2};
		VERIFY(x == BigInt(2));

		x *= x;
		VERIFY(x == BigInt(4));

		x *= x;
		VERIFY(x == BigInt(16));

		x *= x;
		VERIFY(x == BigInt(256));

		x *= -x;
		VERIFY(x == BigInt(-65536));

		x *= x;
		VERIFY(x == BigInt(4294967296));

		x *= -x;
		VERIFY(x == BigInt{"-18446744073709551616"});

		x *= x;
		VERIFY(x == BigInt{"340282366920938463463374607431768211456"});
	}
	return true;
}

GTEST_TEST(BigIntTest, MulEqualTest)
{
	EXPECT_TRUE(MulEqualTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest<hamon::uint2048_t>());

	EXPECT_TRUE(MulEqualTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest2<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(MulEqualTest2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest2<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulEqualTest2<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(MulEqualTest2<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_mul_equal_test

}	// namespace hamon_bigint_test
