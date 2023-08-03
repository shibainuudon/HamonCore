/**
 *	@file	unit_test_bigint_or_equal.cpp
 *
 *	@brief	operator|=のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_or_equal_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
OrEqualTest()
{
	{
		auto x = BigInt{0};
		VERIFY(x == 0);

		x |= BigInt(1);
		VERIFY(x == 0x0001);

		x |= BigInt(0x8000);
		VERIFY(x == 0x8001);
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
OrEqualTest2()
{
	{
		auto x = BigInt{0x8001};
		VERIFY(x == 0x8001);

		x |= BigInt{"0xFEDCBA9876543210000000000000000"};
		VERIFY(x == BigInt{"0xFEDCBA9876543210000000000008001"});

		x |= BigInt{"0x0000FFFF"};
		VERIFY(x == BigInt{"0xFEDCBA987654321000000000000FFFF"});
	}
	return true;
}

GTEST_TEST(BigIntTest, OrEqualTest)
{
	EXPECT_TRUE(OrEqualTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::uint2048_t>());

	EXPECT_TRUE(OrEqualTest2<hamon::bigint>());

	EXPECT_TRUE(OrEqualTest2<hamon::int128_t>());
	EXPECT_TRUE(OrEqualTest2<hamon::int256_t>());
	EXPECT_TRUE(OrEqualTest2<hamon::int512_t>());
	EXPECT_TRUE(OrEqualTest2<hamon::int1024_t>());
	EXPECT_TRUE(OrEqualTest2<hamon::int2048_t>());

	EXPECT_TRUE(OrEqualTest2<hamon::uint128_t>());
	EXPECT_TRUE(OrEqualTest2<hamon::uint256_t>());
	EXPECT_TRUE(OrEqualTest2<hamon::uint512_t>());
	EXPECT_TRUE(OrEqualTest2<hamon::uint1024_t>());
	EXPECT_TRUE(OrEqualTest2<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_or_equal_test

}	// namespace hamon_bigint_test
