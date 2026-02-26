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
		VERIFY((BigInt{0x35} & BigInt{0xf0}) == BigInt{0x30});
		VERIFY((BigInt{0x35} & BigInt{0x0f}) == BigInt{0x05});
		VERIFY((BigInt{0x0F} & BigInt{0x12}) == BigInt{0x02});
		VERIFY((BigInt{0x77} & BigInt{0x20}) == BigInt{0x20});
		VERIFY((BigInt{0x123456} & BigInt{0xf00000}) == BigInt{0x100000});
		VERIFY((BigInt{0x123456} & BigInt{0x0f0000}) == BigInt{0x020000});
		VERIFY((BigInt{0x123456} & BigInt{0x00000f}) == BigInt{0x000006});
		VERIFY((BigInt{0x123456} & BigInt{0xf0f0f0}) == BigInt{0x103050});
	}
	{
		VERIFY((BigInt{0x35} & hamon::uint8_t{0xf0}) == BigInt{0x30});
		VERIFY((BigInt{0x35} & hamon::uint8_t{0x0f}) == BigInt{0x05});
		VERIFY((BigInt{0x0F} & hamon::uint16_t{0x12}) == BigInt{0x02});
		VERIFY((BigInt{0x77} & hamon::uint16_t{0x20}) == BigInt{0x20});
		VERIFY((BigInt{0x123456} & hamon::uint32_t{0xf00000}) == BigInt{0x100000});
		VERIFY((BigInt{0x123456} & hamon::uint32_t{0x0f0000}) == BigInt{0x020000});
		VERIFY((BigInt{0x123456} & hamon::uint64_t{0x00000f}) == BigInt{0x000006});
		VERIFY((BigInt{0x123456} & hamon::uint64_t{0xf0f0f0}) == BigInt{0x103050});
	}
	{
		VERIFY((hamon::uint8_t{0x35} & BigInt{0xf0}) == BigInt{0x30});
		VERIFY((hamon::uint8_t{0x35} & BigInt{0x0f}) == BigInt{0x05});
		VERIFY((hamon::uint16_t{0x0F} & BigInt{0x12}) == BigInt{0x02});
		VERIFY((hamon::uint16_t{0x77} & BigInt{0x20}) == BigInt{0x20});
		VERIFY((hamon::uint32_t{0x123456} & BigInt{0xf00000}) == BigInt{0x100000});
		VERIFY((hamon::uint32_t{0x123456} & BigInt{0x0f0000}) == BigInt{0x020000});
		VERIFY((hamon::uint64_t{0x123456} & BigInt{0x00000f}) == BigInt{0x000006});
		VERIFY((hamon::uint64_t{0x123456} & BigInt{0xf0f0f0}) == BigInt{0x103050});
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
		VERIFY(x == BigInt{0});
	}
	{
		auto x =
			BigInt{"0x0FF00FFF000FFFF0000FFFFF00000FFF"} &
			BigInt{"0x234567890ABCDEF0123456789ABCDEF0"};
		VERIFY(x == BigInt{"0x03400789000CDEF00004567800000EF0"});
	}
	{
		auto x =
			BigInt{"0xFFFF"} &
			BigInt{"0x234567890ABCDEF0123456789ABCDEF0"};
		VERIFY(x == BigInt{"0xDEF0"});
	}
	{
		auto x =
			BigInt{"0x1234000000000000000000000000000"} &
			BigInt{0x123};
		VERIFY(x == BigInt{0});
	}
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntTest, AndTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(AndTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest<hamon::inplace_bigint<127>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest<hamon::inplace_bigint<255>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest<hamon::inplace_bigint<1023>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AndTest<hamon::uint2048_t>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(AndTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest2<hamon::inplace_bigint<999>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest2<hamon::inplace_bigint<1000>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AndTest2<hamon::inplace_bigint<1100>>());

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

}	// namespace bigint_and_test

}	// namespace hamon_bigint_test
