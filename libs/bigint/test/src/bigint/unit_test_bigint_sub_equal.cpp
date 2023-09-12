/**
 *	@file	unit_test_bigint_sub_equal.cpp
 *
 *	@brief	operator-=のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_sub_equal_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
SubEqualTest()
{
	BigInt x = 9630;
	VERIFY(x == BigInt(9630));

	x -= 0;
	VERIFY(x == BigInt(9630));

	x -= 5248;
	VERIFY(x == BigInt(4382));

	x -= BigInt{3758};
	VERIFY(x == BigInt(624));

	x -= 623;
	VERIFY(x == BigInt(1));

	x -= 2;
	VERIFY(x == BigInt(-1));

	x -= BigInt{12};
	VERIFY(x == BigInt(-13));

	x -= BigInt(-30);
	VERIFY(x == BigInt(17));

	x -= BigInt(45);
	VERIFY(x == BigInt(-28));

	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
SubEqualTest2()
{
	auto x = BigInt("8427663852327746832635939785432364562824");

	x -= BigInt{"7567723894568827633575594573939298395955"};
	VERIFY(x == BigInt{"859939957758919199060345211493066166869"});

	x -= BigInt{"192487981375987101002310154809111942081094"};
	VERIFY(x == BigInt{"-191628041418228181803249809597618875914225"});

	return true;
}

GTEST_TEST(BigIntTest, SubEqualTest)
{
	EXPECT_TRUE(SubEqualTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubEqualTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubEqualTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubEqualTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubEqualTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubEqualTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubEqualTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubEqualTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubEqualTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubEqualTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubEqualTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubEqualTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubEqualTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubEqualTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubEqualTest<hamon::uint2048_t>());

	EXPECT_TRUE(SubEqualTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubEqualTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubEqualTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubEqualTest2<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubEqualTest2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubEqualTest2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubEqualTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubEqualTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubEqualTest2<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubEqualTest2<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubEqualTest2<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_sub_equal_test

}	// namespace hamon_bigint_test

