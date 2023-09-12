/**
 *	@file	unit_test_bigint_shift_left_equal.cpp
 *
 *	@brief	operator<<=のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_shift_left_equal_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
ShiftLeftEqualTest()
{
	{
		auto x = BigInt{1};
		VERIFY(x == 0x01);

		x <<= 1;
		VERIFY(x == 0x02);

		x <<= 1;
		VERIFY(x == 0x04);

		x <<= 2;
		VERIFY(x == 0x10);

		x <<= 4;
		VERIFY(x == 0x100);
	}
	{
		auto x = BigInt{0xff};
		VERIFY(x == 0xff);

		x <<= 4;
		VERIFY(x == 0xff0);

		x <<= 8;
		VERIFY(x == 0xff000);
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
ShiftLeftEqualTest2()
{
	{
		auto x = BigInt{1};

		x <<= 100;
		VERIFY(x == BigInt{"0x10000000000000000000000000"});
	}
	{
		auto x = BigInt{"0x123456789ABCDEF"};

		x <<= 67;
		VERIFY(x == BigInt{"0x91a2b3c4d5e6f780000000000000000"});
	}
	return true;
}

GTEST_TEST(BigIntTest, ShiftLeftEqualTest)
{
	EXPECT_TRUE(ShiftLeftEqualTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftEqualTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftEqualTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftEqualTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftEqualTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftEqualTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ShiftLeftEqualTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ShiftLeftEqualTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftEqualTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftEqualTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftEqualTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftEqualTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftEqualTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ShiftLeftEqualTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ShiftLeftEqualTest<hamon::uint2048_t>());

	EXPECT_TRUE(ShiftLeftEqualTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftEqualTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftEqualTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftEqualTest2<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ShiftLeftEqualTest2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ShiftLeftEqualTest2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftEqualTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftEqualTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftEqualTest2<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ShiftLeftEqualTest2<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ShiftLeftEqualTest2<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_shift_left_equal_test

}	// namespace hamon_bigint_test
