/**
 *	@file	unit_test_bigint_sub.cpp
 *
 *	@brief	operator-のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_sub_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
SubTest()
{
	{
		VERIFY(BigInt{0} - BigInt{0} == BigInt(0));
		VERIFY(BigInt{1} - BigInt{0} == BigInt(1));
		VERIFY(BigInt{5} - BigInt{2} == BigInt(3));
		VERIFY(BigInt{1000} - BigInt{1} == BigInt(999));
		VERIFY(BigInt{1000} - BigInt{999} == BigInt(1));
		VERIFY(BigInt{1000} - BigInt{1000} == BigInt(0));
		VERIFY(BigInt{1000} - BigInt{1001} == BigInt(-1));
		VERIFY(BigInt( 2) - BigInt( 5) == BigInt(-3));
		VERIFY(BigInt( 2) - BigInt(-5) == BigInt(7));
		VERIFY(BigInt(-2) - BigInt( 5) == BigInt(-7));
		VERIFY(BigInt(-2) - BigInt(-5) == BigInt(3));
		VERIFY(BigInt{256} - BigInt{1} == BigInt(255));
		VERIFY(BigInt{0x10000} - BigInt{1} == BigInt(0xffff));
		VERIFY(BigInt{0x1000000} - BigInt{1} == BigInt(0xffffff));
		VERIFY(BigInt{0x1000000} - BigInt{0xffffff} == BigInt(1));
	}
	{
		VERIFY(BigInt{0} - hamon::uint8_t{0} == BigInt(0));
		VERIFY(BigInt{1} - hamon::uint16_t{0} == BigInt(1));
		VERIFY(BigInt{5} - hamon::uint32_t{2} == BigInt(3));
		VERIFY(BigInt{1000} - hamon::uint64_t{1} == BigInt(999));
		VERIFY(BigInt{1000} - 999 == BigInt(1));
		VERIFY(BigInt{1000} - 1000 == BigInt(0));
		VERIFY(BigInt{1000} - 1001 == BigInt(-1));
		VERIFY(BigInt( 2) - hamon::int8_t( 5) == BigInt(-3));
		VERIFY(BigInt( 2) - hamon::int16_t(-5) == BigInt(7));
		VERIFY(BigInt(-2) - hamon::int32_t( 5) == BigInt(-7));
		VERIFY(BigInt(-2) - hamon::int64_t(-5) == BigInt(3));
		VERIFY(BigInt{256} - int{1} == BigInt(255));
		VERIFY(BigInt{0x10000} - short{1} == BigInt(0xffff));
		VERIFY(BigInt{0x1000000} - long{1} == BigInt(0xffffff));
		VERIFY(BigInt{0x1000000} - hamon::uint64_t{0xffffff} == BigInt(1));
	}
	{
		VERIFY(hamon::uint8_t{0} - BigInt{0} == BigInt(0));
		VERIFY(hamon::uint16_t{1} - BigInt{0} == BigInt(1));
		VERIFY(hamon::uint32_t{5} - BigInt{2} == BigInt(3));
		VERIFY(hamon::uint64_t{1000} - BigInt{1} == BigInt(999));
		VERIFY(1000 - BigInt{999} == BigInt(1));
		VERIFY(1000 - BigInt{1000} == BigInt(0));
		VERIFY(1000 - BigInt{1001} == BigInt(-1));
		VERIFY(hamon::int8_t( 2) - BigInt( 5) == BigInt(-3));
		VERIFY(hamon::int16_t( 2) - BigInt(-5) == BigInt(7));
		VERIFY(hamon::int32_t(-2) - BigInt( 5) == BigInt(-7));
		VERIFY(hamon::int64_t(-2) - BigInt(-5) == BigInt(3));
		VERIFY(long{256} - BigInt{1} == BigInt(255));
		VERIFY(hamon::uint32_t{0x10000} - BigInt{1} == BigInt(0xffff));
		VERIFY(hamon::uint64_t{0x1000000} - BigInt{1} == BigInt(0xffffff));
		VERIFY(hamon::uint64_t{0x1000000} - BigInt{0xffffff} == BigInt(1));
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
SubTest2()
{
	{
		auto x =
			BigInt{"8427663852327746832635939785432364562824"} -
			BigInt{"7567723894568827633575594573939298395955"};
		VERIFY(x == BigInt{"859939957758919199060345211493066166869"});
	}
	{
		auto x =
			BigInt{"4831358420296681146974351689067644777329"} -
			BigInt{"8250655382930189933211483422173351786903"};
		VERIFY(x == BigInt{"-3419296962633508786237131733105707009574"});
	}
	{
		auto x =
			BigInt{"100000000000000000000000000000000000000"} -
			BigInt{1};
		VERIFY(x == BigInt{"99999999999999999999999999999999999999"});
	}
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntTest, SubTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(SubTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<hamon::inplace_bigint<128>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<hamon::inplace_bigint<256>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<hamon::inplace_bigint<512>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubTest<hamon::uint2048_t>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(SubTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest2<hamon::inplace_bigint<128>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest2<hamon::inplace_bigint<256>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest2<hamon::inplace_bigint<512>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest2<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubTest2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubTest2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest2<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubTest2<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubTest2<hamon::uint2048_t>());
}

}	// namespace bigint_sub_test

}	// namespace hamon_bigint_test

