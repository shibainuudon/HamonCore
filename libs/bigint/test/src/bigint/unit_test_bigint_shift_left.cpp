/**
 *	@file	unit_test_bigint_shift_left.cpp
 *
 *	@brief	operator<<のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_shift_left_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
ShiftLeftTest()
{
	{
		auto x = BigInt{0x1234} << 1;
		VERIFY(x == BigInt(0x2468));
	}
	{
		auto x = BigInt{0x1234} << 8;
		VERIFY(x == BigInt(0x123400));
	}
	{
		auto x = BigInt{0x1234} << 31;
		VERIFY(x == BigInt(0x91a00000000ULL));
	}
	{
		auto x = BigInt{0x1234} << 32;
		VERIFY(x == BigInt(0x123400000000ULL));
	}
	{
		auto x = BigInt{0x1234} << 33;
		VERIFY(x == BigInt(0x246800000000ULL));
	}
	{
		auto x = BigInt{0x1234} << 34;
		VERIFY(x == BigInt(0x48d000000000ULL));
	}
	{
		auto x = BigInt{0x1234} << 40;
		VERIFY(x == BigInt(0x12340000000000ULL));
	}
	{
		auto x = BigInt{0x1234} << 41;
		VERIFY(x == BigInt(0x24680000000000ULL));
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
ShiftLeftTest2()
{
	{
		auto x = BigInt{0x1234} << 64;
		VERIFY(x == BigInt{"0x12340000000000000000"});
	}
	{
		auto x = BigInt{0x1234} << 65;
		VERIFY(x == BigInt{"0x24680000000000000000"});
	}
	{
		auto x = BigInt{0x1234} << 128;
		VERIFY(x == BigInt{"0x123400000000000000000000000000000000"});
	}
	{
		auto x = BigInt{0x1234} << 255;
		VERIFY(x == BigInt{"0x91A0000000000000000000000000000000000000000000000000000000000000000"});
	}
	return true;
}

GTEST_TEST(BigIntTest, ShiftLeftTest)
{
	EXPECT_TRUE(ShiftLeftTest<hamon::bigint>());

//	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest<hamon::int2048_t>());

//	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest<hamon::uint2048_t>());

	EXPECT_TRUE(ShiftLeftTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest2<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest2<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest2<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest2<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftTest2<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_shift_left_test

}	// namespace hamon_bigint_test
