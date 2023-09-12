/**
 *	@file	unit_test_bigint_mod_equal.cpp
 *
 *	@brief	operator%=のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_mod_equal_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
UnsignedModEqualTest()
{
	{
		auto x = BigInt{12345};
		VERIFY(x == 12345);

		x %= BigInt(678);
		VERIFY(x == 141);

		x %= BigInt{13};
		VERIFY(x == 11);

		x %= BigInt(20);
		VERIFY(x == 11);

		x %= BigInt{11};
		VERIFY(x == 0);

		x %= BigInt(1);
		VERIFY(x == 0);
	}
	{
		BigInt x{0xffff};
		VERIFY(x == 0xffff);

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
		x %= x;
		VERIFY(x == 0);
HAMON_WARNING_POP()
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
SignedModEqualTest()
{
	{
		auto x = BigInt(-51);
		VERIFY(x == BigInt(-51));

		x %= BigInt(13);
		VERIFY(x == BigInt(-12));

		x %= BigInt(-7);
		VERIFY(x == BigInt(-5));

		x %= BigInt(5);
		VERIFY(x == BigInt(0));
	}
	return true;
}

GTEST_TEST(BigIntTest, ModEqualTest)
{
	EXPECT_TRUE(UnsignedModEqualTest<hamon::bigint>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModEqualTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModEqualTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModEqualTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModEqualTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModEqualTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedModEqualTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedModEqualTest<hamon::int2048_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModEqualTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModEqualTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModEqualTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModEqualTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModEqualTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedModEqualTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedModEqualTest<hamon::uint2048_t>());

	EXPECT_TRUE(SignedModEqualTest<hamon::bigint>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedModEqualTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedModEqualTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedModEqualTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedModEqualTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedModEqualTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SignedModEqualTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SignedModEqualTest<hamon::int2048_t>());
}

#undef VERIFY

}	// namespace bigint_mod_equal_test

}	// namespace hamon_bigint_test
