/**
 *	@file	unit_test_bigint_or_equal.cpp
 *
 *	@brief	operator|=のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_or_equal_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
OrEqualTest()
{
	{
		auto x = BigInt{0};
		VERIFY(x == BigInt{0});

		x |= BigInt(1);
		VERIFY(x == BigInt{0x0001});

		x |= BigInt(0x8000);
		VERIFY(x == BigInt{0x8001});
	}
	{
		auto x = BigInt{0};

		x |= hamon::uint8_t(0x40);
		VERIFY(x == BigInt{0x0040});

		x |= hamon::uint16_t(0x8001);
		VERIFY(x == BigInt{0x8041});

		x |= hamon::uint32_t(0xff00ff00);
		VERIFY(x == BigInt{0xff00ff41});

		x |= hamon::uint64_t(0x123456789abcdef0);
		VERIFY(x == BigInt{0x12345678ffbcfff1});
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
OrEqualTest2()
{
	{
		auto x = BigInt{0x8001};
		VERIFY(x == BigInt{0x8001});

		x |= BigInt{"0xFEDCBA9876543210000000000000000"};
		VERIFY(x == BigInt{"0xFEDCBA9876543210000000000008001"});

		x |= BigInt{"0x0000FFFF"};
		VERIFY(x == BigInt{"0xFEDCBA987654321000000000000FFFF"});
	}
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntTest, OrEqualTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::inplace_bigint<128>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::inplace_bigint<256>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::inplace_bigint<512>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(OrEqualTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(OrEqualTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(OrEqualTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(OrEqualTest<hamon::uint2048_t>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(OrEqualTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest2<hamon::inplace_bigint<128>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest2<hamon::inplace_bigint<256>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest2<hamon::inplace_bigint<512>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest2<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(OrEqualTest2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(OrEqualTest2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OrEqualTest2<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(OrEqualTest2<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(OrEqualTest2<hamon::uint2048_t>());
}

}	// namespace bigint_or_equal_test

}	// namespace hamon_bigint_test
