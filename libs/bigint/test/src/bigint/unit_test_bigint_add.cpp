/**
 *	@file	unit_test_bigint_add.cpp
 *
 *	@brief	operator+のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_add_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
AddTest()
{
	{
		VERIFY(BigInt(0) + BigInt(0) == BigInt(0));
		VERIFY(BigInt(1) + BigInt(0) == BigInt(1));
		VERIFY(BigInt(2) + BigInt(3) == BigInt(5));
		VERIFY(BigInt(2) + BigInt(-3) == BigInt(-1));
		VERIFY(BigInt(-2) + BigInt(3) == BigInt(1));
		VERIFY(BigInt(-2) + BigInt(-3) == BigInt(-5));
		VERIFY(BigInt(1) + BigInt(999) == BigInt(1000));
		VERIFY(BigInt(-10) + BigInt(1000) == BigInt(990));
		VERIFY(BigInt(255) + BigInt(1) == BigInt(256));
		VERIFY(BigInt(256) + BigInt(-1) == BigInt(255));
		VERIFY(BigInt(255) + BigInt(255) == BigInt(510));
		VERIFY(BigInt(255) + BigInt(256) == BigInt(511));
		VERIFY(BigInt(0xffff) + BigInt(1) == BigInt(0x10000));
		VERIFY(BigInt(1) + BigInt(0xffffff) == BigInt(0x1000000));
		VERIFY(BigInt(0xffffffff) + BigInt(0xffffffff) == BigInt(0x1fffffffe));
	}
	{
		VERIFY(BigInt{0} + hamon::uint8_t{0} == BigInt{0});
		VERIFY(BigInt{1} + hamon::uint16_t{0} == BigInt{1});
		VERIFY(BigInt{2} + hamon::uint32_t{3} == BigInt{5});
		VERIFY(BigInt{2} + hamon::int8_t(-3) == BigInt{-1});
		VERIFY(BigInt{-2} + hamon::uint64_t{3} == BigInt{1});
		VERIFY(BigInt{-2} + hamon::int16_t{-3} == BigInt{-5});
		VERIFY(BigInt{1} + hamon::int32_t{999} == BigInt{1000});
		VERIFY(BigInt{-10} + hamon::int32_t{1000} == BigInt{990});
		VERIFY(BigInt{255} + hamon::int16_t{ 1} == BigInt{256});
		VERIFY(BigInt{256} + hamon::int16_t{-1} == BigInt{255});
		VERIFY(BigInt{255} + hamon::uint32_t{255} == BigInt{510});
		VERIFY(BigInt{255} + hamon::uint32_t{256} == BigInt{511});
		VERIFY(BigInt{0xffff} + hamon::int32_t{1} == BigInt{0x10000});
		VERIFY(BigInt{1} + hamon::int64_t{0xffffff} == BigInt{0x1000000});
		VERIFY(BigInt{0xffffffff} + hamon::uint64_t{0xffffffff} == BigInt{0x1fffffffe});
	}
	{
		VERIFY(hamon::uint8_t(0) + BigInt(0) == BigInt(0));
		VERIFY(hamon::uint16_t(1) + BigInt(0) == BigInt(1));
		VERIFY(hamon::uint32_t(2) + BigInt(3) == BigInt(5));
		VERIFY(hamon::uint64_t(2) + BigInt(-3) == BigInt(-1));
		VERIFY(hamon::int8_t(-2) + BigInt(3) == BigInt(1));
		VERIFY(hamon::int16_t(-2) + BigInt(-3) == BigInt(-5));
		VERIFY(hamon::int32_t(1) + BigInt(999) == BigInt(1000));
		VERIFY(hamon::int64_t(-10) + BigInt(1000) == BigInt(990));
		VERIFY(hamon::int16_t(255) + BigInt(1) == BigInt(256));
		VERIFY(hamon::uint16_t(256) + BigInt(-1) == BigInt(255));
		VERIFY(hamon::int32_t(255) + BigInt(255) == BigInt(510));
		VERIFY(hamon::uint32_t(255) + BigInt(256) == BigInt(511));
		VERIFY(hamon::uint64_t(0xffff) + BigInt(1) == BigInt(0x10000));
		VERIFY(hamon::uint64_t(1) + BigInt(0xffffff) == BigInt(0x1000000));
		VERIFY(hamon::uint64_t(0xffffffff) + BigInt(0xffffffff) == BigInt(0x1fffffffe));
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
AddTest2()
{
	{
		auto x =
			BigInt{"3565257399734975859457283787877529836964"} +
			BigInt{"7966969762968552357477389456772596794377"};
		VERIFY(x == BigInt{"11532227162703528216934673244650126631341"});
	}
	{
		auto x =
			BigInt{"3565257399734975859457283787877529836964"} +
			BigInt{"-7966969762968552357477389456772596794377"};
		VERIFY(x == BigInt{"-4401712363233576498020105668895066957413"});
	}
	{
		auto x =
			BigInt{"99999999999999999999999999999999999999"} +
			BigInt(1);
		VERIFY(x == BigInt{"100000000000000000000000000000000000000"});
	}
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntTest, AddTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::inplace_bigint<128>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::inplace_bigint<2048>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::inplace_bigint<4096>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AddTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AddTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AddTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AddTest<hamon::uint2048_t>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(AddTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest2<hamon::inplace_bigint<200>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest2<hamon::inplace_bigint<500>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest2<hamon::inplace_bigint<1000>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest2<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AddTest2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AddTest2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest2<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AddTest2<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(AddTest2<hamon::uint2048_t>());
}

}	// namespace bigint_add_test

}	// namespace hamon_bigint_test
