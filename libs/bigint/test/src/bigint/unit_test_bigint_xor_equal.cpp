/**
 *	@file	unit_test_bigint_xor_equal.cpp
 *
 *	@brief	operator^=のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_xor_equal_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
XorEqualTest()
{
	{
		auto x = BigInt{0};
		VERIFY(x == BigInt(0));

		x ^= BigInt(1);
		VERIFY(x == BigInt(0x0001));

		x ^= BigInt(1);
		VERIFY(x == BigInt(0x0000));

		x ^= BigInt(0x1234);
		VERIFY(x == BigInt(0x1234));

		x ^= BigInt(0xff00);
		VERIFY(x == BigInt(0xed34));
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
XorEqualTest2()
{
	{
		auto x = BigInt{"0x123456789ABCDEF0123456789ABCDEF"};
		VERIFY(x == BigInt{"0x123456789ABCDEF0123456789ABCDEF"});

		x ^= BigInt{"0xFFFF0000FFFFF00000FF00F0F0FFF00"};
		VERIFY(x == BigInt{"0x0edcb567865432ef012cb56886a432ef"});

		x ^= BigInt{"0x0edcb567865432ef012cb56886a432ef"};
		VERIFY(x == 0);
	}
	return true;
}

GTEST_TEST(BigIntTest, XorEqualTest)
{
	EXPECT_TRUE(XorEqualTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest<hamon::uint2048_t>());

	EXPECT_TRUE(XorEqualTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest2<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest2<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest2<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest2<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorEqualTest2<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_xor_equal_test

}	// namespace hamon_bigint_test
