/**
 *	@file	unit_test_bigint_and.cpp
 *
 *	@brief	operator&のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_and_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
AndTest()
{
	{
		auto x = BigInt{0x35} & BigInt{0xf0};
		VERIFY(x == 0x30);
	}
	{
		auto x = BigInt{0x35} & BigInt{0x0f};
		VERIFY(x == 0x05);
	}
	{
		auto x = BigInt{0x0F} & BigInt{0x12};
		VERIFY(x == 0x02);
	}
	{
		auto x = BigInt{0x77} & BigInt{0x20};
		VERIFY(x == 0x20);
	}
	{
		auto x = BigInt{0x123456} & BigInt{0xf00000};
		VERIFY(x == 0x100000);
	}
	{
		auto x = BigInt{0x123456} & BigInt{0x0f0000};
		VERIFY(x == 0x020000);
	}
	{
		auto x = BigInt{0x123456} & BigInt{0x00000f};
		VERIFY(x == 0x000006);
	}
	{
		auto x = BigInt{0x123456} & BigInt{0xf0f0f0};
		VERIFY(x == 0x103050);
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
AndTest2()
{
	{
		auto x =
			BigInt{0x01} &
			BigInt{"0x8000000000000000000000000000000"};
		VERIFY(x == 0);
	}
	{
		auto x =
			BigInt{"0xF0FF00FFF000FFFF0000FFFFF00000FFF"} &
			BigInt{"0x1234567890ABCDEF0123456789ABCDEF0"};
		VERIFY(x == BigInt{"0x103400789000CDEF00004567800000EF0"});
	}
	{
		auto x =
			BigInt{"0x1234000000000000000000000000000"} &
			BigInt{0x123};
		VERIFY(x == 0);
	}
	return true;
}

GTEST_TEST(BigIntTest, AndTest)
{
	EXPECT_TRUE(AndTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndTest<hamon::uint2048_t>());

	EXPECT_TRUE(AndTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest2<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndTest2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndTest2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest2<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndTest2<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndTest2<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_and_test

}	// namespace hamon_bigint_test
