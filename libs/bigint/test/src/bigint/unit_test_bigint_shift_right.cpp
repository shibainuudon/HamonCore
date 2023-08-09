/**
 *	@file	unit_test_bigint_shift_right.cpp
 *
 *	@brief	operator>>のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_shift_right_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
ShiftRightTest()
{
	{
		auto x = BigInt{0x1234} >> 1;
		VERIFY(x == 0x91a);
	}
	{
		auto x = BigInt{0xffff} >> 1;
		VERIFY(x == 0x7fff);
	}
	{
		auto x = BigInt{0xffffff} >> 2;
		VERIFY(x == 0x3fffff);
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
ShiftRightTest2()
{
	{
		auto x = BigInt{"0x12340000000000000000"} >> 64;
		VERIFY(x == 0x1234);
	}
	{
		auto x = BigInt{"0x12340000000000000000"} >> 65;
		VERIFY(x == 0x91a);
	}
	return true;
}

GTEST_TEST(BigIntTest, ShiftRightTest)
{
	EXPECT_TRUE(ShiftRightTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest<hamon::uint2048_t>());

	EXPECT_TRUE(ShiftRightTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest2<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest2<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest2<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest2<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightTest2<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_shift_right_test

}	// namespace hamon_bigint_test
