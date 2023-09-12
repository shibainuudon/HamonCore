/**
 *	@file	unit_test_bigint_and_equal.cpp
 *
 *	@brief	operator&=のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_and_equal_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
AndEqualTest()
{
	{
		auto x = BigInt(0xffffffff);
		VERIFY(x == BigInt(0xffffffff));

		x &= BigInt(0x80ff000f);
		VERIFY(x == BigInt(0x80ff000f));

		x &= BigInt(0x0000ffff);
		VERIFY(x == BigInt(0x0000000f));

		x &= BigInt(1);
		VERIFY(x == BigInt(0x00000001));
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
AndEqualTest2()
{
	{
		auto x = BigInt{0xffffffff};
		VERIFY(x == 0xffffffff);

		x &= BigInt("0xFEDCBA9876543210000000000000000");
		VERIFY(x == 0);
	}
	{
		auto x = BigInt{0x12345678};
		VERIFY(x == 0x12345678);

		x &= BigInt("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
		VERIFY(x == 0x12345678);

		x &= BigInt("0x000000000000000000000000000FFFF");
		VERIFY(x == 0x5678);
	}
	return true;
}

GTEST_TEST(BigIntTest, AndEqualTest)
{
	EXPECT_TRUE(AndEqualTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndEqualTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndEqualTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndEqualTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndEqualTest<hamon::uint2048_t>());

	EXPECT_TRUE(AndEqualTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest2<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndEqualTest2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndEqualTest2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest2<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndEqualTest2<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndEqualTest2<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_and_equal_test

}	// namespace hamon_bigint_test
