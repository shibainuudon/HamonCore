/**
 *	@file	unit_test_bigint_or.cpp
 *
 *	@brief	operator|のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_or_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
OrTest()
{
	{
		VERIFY((BigInt{0x0F} | BigInt{0x35}) == BigInt{0x3F});
		VERIFY((BigInt{0x35} | BigInt{0xf0}) == BigInt{0xF5});
		VERIFY((BigInt{0x0F} | BigInt{0x12}) == BigInt{0x1F});
		VERIFY((BigInt{0x77} | BigInt{0x20}) == BigInt{0x77});
		VERIFY((BigInt{0x123456} | BigInt{0xf00000}) == BigInt{0xF23456});
		VERIFY((BigInt{0x123456} | BigInt{0x0f0000}) == BigInt{0x1F3456});
		VERIFY((BigInt{0x123456} | BigInt{0x00000f}) == BigInt{0x12345F});
		VERIFY((BigInt{0x123456} | BigInt{0xf0f0f0}) == BigInt{0xF2F4F6});
	}
	{
		VERIFY((BigInt{0x0F} | hamon::uint8_t{0x35}) == BigInt{0x3F});
		VERIFY((BigInt{0x35} | hamon::uint8_t{0xf0}) == BigInt{0xF5});
		VERIFY((BigInt{0x0F} | hamon::uint16_t{0x12}) == BigInt{0x1F});
		VERIFY((BigInt{0x77} | hamon::uint16_t{0x20}) == BigInt{0x77});
		VERIFY((BigInt{0x123456} | hamon::uint32_t{0xf00000}) == BigInt{0xF23456});
		VERIFY((BigInt{0x123456} | hamon::uint32_t{0x0f0000}) == BigInt{0x1F3456});
		VERIFY((BigInt{0x123456} | hamon::uint64_t{0x00000f}) == BigInt{0x12345F});
		VERIFY((BigInt{0x123456} | hamon::uint64_t{0xf0f0f0}) == BigInt{0xF2F4F6});
	}
	{
		VERIFY((hamon::uint8_t{0x0F} | BigInt{0x35}) == BigInt{0x3F});
		VERIFY((hamon::uint8_t{0x35} | BigInt{0xf0}) == BigInt{0xF5});
		VERIFY((hamon::uint16_t{0x0F} | BigInt{0x12}) == BigInt{0x1F});
		VERIFY((hamon::uint16_t{0x77} | BigInt{0x20}) == BigInt{0x77});
		VERIFY((hamon::uint32_t{0x123456} | BigInt{0xf00000}) == BigInt{0xF23456});
		VERIFY((hamon::uint32_t{0x123456} | BigInt{0x0f0000}) == BigInt{0x1F3456});
		VERIFY((hamon::uint64_t{0x123456} | BigInt{0x00000f}) == BigInt{0x12345F});
		VERIFY((hamon::uint64_t{0x123456} | BigInt{0xf0f0f0}) == BigInt{0xF2F4F6});
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
OrTest2()
{
	{
		auto x =
			BigInt{0x01} |
			BigInt{"0x8000000000000000000000000000000"};
		VERIFY(x == BigInt{"0x8000000000000000000000000000001"});
	}
	{
		auto x =
			BigInt{"0x0FF00FFF000FFFF0000FFFFF00000FFF"} |
			BigInt{"0x234567890ABCDEF0123456789ABCDEF0"};
		VERIFY(x == BigInt{"0x2FF56FFF0ABFFFF0123FFFFF9ABCDFFF"});
	}
	{
		auto x =
			BigInt{"0xFFFF"} |
			BigInt{"0x234567890ABCDEF0123456789ABCDEF0"};
		VERIFY(x == BigInt{"0x234567890ABCDEF0123456789ABCFFFF"});
	}
	{
		auto x =
			BigInt{"0x1234000000000000000000000000000"} | 
			BigInt{0x123};
		VERIFY(x == BigInt{"0x1234000000000000000000000000123"});
	}
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntTest, OrTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::inplace_bigint<128>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::inplace_bigint<256>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::inplace_bigint<512>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(OrTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(OrTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(OrTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(OrTest<hamon::uint2048_t>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(OrTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest2<hamon::inplace_bigint<128>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest2<hamon::inplace_bigint<256>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest2<hamon::inplace_bigint<512>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest2<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(OrTest2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(OrTest2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrTest2<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(OrTest2<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(OrTest2<hamon::uint2048_t>());
}

}	// namespace bigint_or_test

}	// namespace hamon_bigint_test
