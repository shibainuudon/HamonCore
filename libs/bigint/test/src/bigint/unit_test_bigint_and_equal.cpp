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
	{
		auto x = BigInt(0x12345678);

		x &= hamon::uint64_t(0xff0000ff);
		VERIFY(x == BigInt(0x12000078));

		x &= hamon::uint32_t(0xffff);
		VERIFY(x == BigInt(0x00000078));

		x &= hamon::uint16_t(0x00f0);
		VERIFY(x == BigInt(0x00000070));

		x &= hamon::uint8_t(0x0040);
		VERIFY(x == BigInt(0x00000040));
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
AndEqualTest2()
{
	{
		auto x = BigInt{0xffffffff};
		VERIFY(x == BigInt{0xffffffff});

		x &= BigInt("0xFEDCBA9876543210000000000000000");
		VERIFY(x == BigInt{0});
	}
	{
		auto x = BigInt{0x12345678};
		VERIFY(x == BigInt{0x12345678});

		x &= BigInt("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
		VERIFY(x == BigInt{0x12345678});

		x &= BigInt("0x000000000000000000000000000FFFF");
		VERIFY(x == BigInt{0x5678});
	}
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntTest, AndEqualTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(AndEqualTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest<hamon::inplace_bigint<256>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest<hamon::inplace_bigint<512>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest<hamon::inplace_bigint<768>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndEqualTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndEqualTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndEqualTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndEqualTest<hamon::uint2048_t>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(AndEqualTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest2<hamon::inplace_bigint<256>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest2<hamon::inplace_bigint<1024>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndEqualTest2<hamon::inplace_bigint<2048>>());

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

}	// namespace bigint_and_equal_test

}	// namespace hamon_bigint_test
