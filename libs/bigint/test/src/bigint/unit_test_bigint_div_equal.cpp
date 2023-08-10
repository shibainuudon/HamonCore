/**
 *	@file	unit_test_bigint_div_equal.cpp
 *
 *	@brief	operator/=のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_div_equal_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
UnsignedDivEqualTest()
{
	{
		BigInt x{100};
		VERIFY(x == 100);

		x /= BigInt{2};
		VERIFY(x == 50);

		x /= BigInt{2};
		VERIFY(x == 25);

		x /= BigInt{2};
		VERIFY(x == 12);

		x /= BigInt{2};
		VERIFY(x == 6);

		x /= BigInt{2};
		VERIFY(x == 3);

		x /= BigInt{2};
		VERIFY(x == 1);

		x /= BigInt{2};
		VERIFY(x == 0);

		x /= BigInt{2};
		VERIFY(x == 0);
	}
	{
		BigInt x{0xffff};
		VERIFY(x == 0xffff);

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
		x /= x;
		VERIFY(x == 1);
HAMON_WARNING_POP()
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
SignedDivEqualTest()
{
	{
		BigInt x(-256);
		VERIFY(x == -256);

		x /= BigInt{2};
		VERIFY(x == -128);

		x /= -2;
		VERIFY(x == 64);

		x /= -4;
		VERIFY(x == -16);

		x /= BigInt{4};
		VERIFY(x == -4);

		x /= BigInt{5};
		VERIFY(x == 0);

		x /= -1;
		VERIFY(x == 0);
	}
	return true;
}

GTEST_TEST(BigIntTest, DivEqualTest)
{
	EXPECT_TRUE(UnsignedDivEqualTest<hamon::bigint>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivEqualTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivEqualTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivEqualTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivEqualTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivEqualTest<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivEqualTest<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivEqualTest<hamon::int2048_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivEqualTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivEqualTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivEqualTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivEqualTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivEqualTest<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivEqualTest<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivEqualTest<hamon::uint2048_t>());

	EXPECT_TRUE(SignedDivEqualTest<hamon::bigint>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivEqualTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivEqualTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivEqualTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivEqualTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivEqualTest<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivEqualTest<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivEqualTest<hamon::int2048_t>());
}

#undef VERIFY

}	// namespace bigint_div_equal_test

}	// namespace hamon_bigint_test
