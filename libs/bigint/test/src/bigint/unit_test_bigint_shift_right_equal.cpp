/**
 *	@file	unit_test_bigint_shift_right_equal.cpp
 *
 *	@brief	operator>>=のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_shift_right_equal_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
ShiftRightEqualTest()
{
	{
		auto x = BigInt{12345678};
		VERIFY(x == 12345678);

		x >>= 1;
		VERIFY(x == 6172839);

		x >>= 2;
		VERIFY(x == 1543209);

		x >>= 3;
		VERIFY(x == 192901);

		x >>= 10;
		VERIFY(x == 188);
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
ShiftRightEqualTest2()
{
	{
		auto x = BigInt{"0x1234567890123456789012345678901234567890"};

		x >>= 4;
		VERIFY(x == BigInt{"0x123456789012345678901234567890123456789"});

		x >>= 0x10000000;
		VERIFY(x == 0);
	}
	return true;
}

GTEST_TEST(BigIntTest, ShiftRightEqualTest)
{
	EXPECT_TRUE(ShiftRightEqualTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightEqualTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightEqualTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightEqualTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightEqualTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightEqualTest<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightEqualTest<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightEqualTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightEqualTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightEqualTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightEqualTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightEqualTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightEqualTest<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightEqualTest<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftRightEqualTest<hamon::uint2048_t>());

	EXPECT_TRUE(ShiftRightEqualTest2<hamon::bigint>());

	EXPECT_TRUE(ShiftRightEqualTest2<hamon::int128_t>());
	EXPECT_TRUE(ShiftRightEqualTest2<hamon::int256_t>());
	EXPECT_TRUE(ShiftRightEqualTest2<hamon::int512_t>());
	EXPECT_TRUE(ShiftRightEqualTest2<hamon::int1024_t>());
	EXPECT_TRUE(ShiftRightEqualTest2<hamon::int2048_t>());

	EXPECT_TRUE(ShiftRightEqualTest2<hamon::uint128_t>());
	EXPECT_TRUE(ShiftRightEqualTest2<hamon::uint256_t>());
	EXPECT_TRUE(ShiftRightEqualTest2<hamon::uint512_t>());
	EXPECT_TRUE(ShiftRightEqualTest2<hamon::uint1024_t>());
	EXPECT_TRUE(ShiftRightEqualTest2<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_shift_right_equal_test

}	// namespace hamon_bigint_test
